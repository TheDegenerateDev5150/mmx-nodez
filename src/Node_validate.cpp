/*
 * Node_validate.cpp
 *
 *  Created on: Jan 20, 2022
 *      Author: mad
 */

#include <mmx/Node.h>
#include <mmx/ProofOfSpaceOG.hxx>
#include <mmx/ProofOfSpaceNFT.hxx>
#include <mmx/contract/PubKey.hxx>
#include <mmx/contract/MultiSig.hxx>
#include <mmx/contract/Binary.hxx>
#include <mmx/contract/Executable.hxx>
#include <mmx/operation/Execute.hxx>
#include <mmx/operation/Deposit.hxx>
#include <mmx/utils.h>
#include <mmx/vm_interface.h>
#include <mmx/exception.h>
#include <mmx/error_code_e.hxx>
#include <mmx/txio_t.hpp>

#include <vnx/vnx.h>


namespace mmx {

void Node::execution_context_t::wait(const hash_t& txid) const
{
	auto iter = wait_map.find(txid);
	if(iter != wait_map.end()) {
		for(const auto& prev : iter->second) {
			auto iter = signal_map.find(prev);
			if(iter != signal_map.end()) {
				auto& entry = iter->second;
				{
					std::unique_lock<std::mutex> lock(entry->mutex);
					while(entry->do_wait) {
						entry->signal.wait(lock);
					}
				}
			}
		}
	}
}

void Node::execution_context_t::signal(const hash_t& txid) const
{
	auto iter = signal_map.find(txid);
	if(iter != signal_map.end()) {
		auto& entry = iter->second;
		{
			std::lock_guard lock(entry->mutex);
			entry->do_wait = false;
		}
		entry->signal.notify_all();
	}
}

void Node::execution_context_t::setup_wait(const hash_t& txid, const addr_t& address)
{
	const auto& list = mutate_map[address];
	if(!list.empty()) {
		wait_map[txid].insert(list.back());
	}
}

std::shared_ptr<Node::execution_context_t> Node::new_exec_context(const uint32_t height) const
{
	auto context = std::make_shared<execution_context_t>();
	context->height = height;
	context->storage = std::make_shared<vm::StorageCache>(storage);
	return context;
}

void Node::prepare_context(std::shared_ptr<execution_context_t> context, std::shared_ptr<const Transaction> tx) const
{
	std::set<addr_t> mutate_set;
	if(tx->deploy) {
		mutate_set.insert(tx->id);
	}
	for(const auto& op : tx->get_operations()) {
		mutate_set.insert(op->address == addr_t() ? tx->id : op->address);
	}
	for(const auto& address : std::vector<addr_t>(mutate_set.begin(), mutate_set.end()))
	{
		std::vector<addr_t> depends;
		if(address == tx->id) {
			if(auto exec = std::dynamic_pointer_cast<const contract::Executable>(tx->deploy)) {
				depends = get_all_depends(exec);
			}
		} else {
			depends = get_all_depends(address, 1);
		}
		mutate_set.insert(depends.begin(), depends.end());
	}
	for(const auto& address : mutate_set) {
		context->setup_wait(tx->id, address);
		context->mutate_map[address].push_back(tx->id);
	}
	if(!mutate_set.empty()) {
		context->signal_map.emplace(tx->id, std::make_shared<waitcond_t>());
	}
}

std::shared_ptr<Node::execution_context_t> Node::validate(std::shared_ptr<const Block> block) const
{
	/*
	 * The following fields have already been verified in `Node::verify_proof()` or see note:
	 * - vdf_height
	 * - vdf_count				(Node::find_vdf_points() + Node::verify_proof())
	 * - vdf_iters
	 * - vdf_output				(Node::find_vdf_points())
	 * - vdf_reward_addr		(Node::find_vdf_points())
	 * - proof
	 * - proof_hash
	 * - challenge
	 * - is_space_fork
	 * - time_diff
	 * - space_diff
	 * - proof_score_sum
	 * - proof_score_count
	 * - weight
	 * - total_weight
	 */

	if(!block->is_valid()) {
		throw std::logic_error("static validation failed");
	}
	block->validate();

	const auto prev = find_prev(block);
	if(!prev) {
		throw std::logic_error("missing prev");
	}
	if(prev->hash != state_hash) {
		throw std::logic_error("state mismatch");
	}
	if(block->version != 0) {
		throw std::logic_error("invalid version");
	}
	if(block->height != prev->height + 1) {
		throw std::logic_error("invalid height");
	}
	if(block->space_fork_len > params->challenge_interval * 100) {
		throw std::logic_error("space fork too long");
	}
	if(block->time_stamp - prev->time_stamp > block->vdf_count * params->block_interval_ms * 2) {
		throw std::logic_error("time stamp delta too high");
	}
	if(block->time_stamp - prev->time_stamp < block->vdf_count * params->block_interval_ms / 2) {
		throw std::logic_error("time stamp delta too low");
	}
	if(block->time_diff < params->time_diff_divider || block->space_diff == 0) {
		throw std::logic_error("invalid difficulty");
	}
	if(block->static_cost > params->max_block_size) {
		throw std::logic_error("block size too high: " + std::to_string(block->static_cost));
	}
	if(block->total_cost > params->max_block_cost) {
		throw std::logic_error("block cost too high: " + std::to_string(block->total_cost));
	}
	const auto txfee_buffer = calc_new_txfee_buffer(params, prev);
	if(block->txfee_buffer != txfee_buffer) {
		throw std::logic_error("invalid txfee_buffer: " + std::to_string(block->txfee_buffer) + " != " + std::to_string(txfee_buffer));
	}
	if(block->reward_vote > 1 || block->reward_vote < -1) {
		throw std::logic_error("invalid reward_vote: " + std::to_string(block->reward_vote));
	}
	vnx::optional<addr_t> reward_contract;

	if(block->reward_addr) {
		if(auto proof = std::dynamic_pointer_cast<const ProofOfSpaceNFT>(block->proof[0])) {
			reward_contract = proof->contract;
		}
	}
	if(block->reward_contract != reward_contract) {
		throw std::logic_error("invalid reward_contract");
	}
	if(reward_contract) {
		addr_t target;
		try {
			target = get_plot_nft_target(*reward_contract, block->reward_account);
		} catch(const std::exception& ex) {
			throw std::logic_error("reward_addr resolution failed with: " + std::string(ex.what()));
		}
		if(!block->reward_addr || (*block->reward_addr) != target) {
			throw std::logic_error("invalid reward_addr for reward_contract: expected " + target.to_string());
		}
	}

	if(block->height % params->vdf_reward_interval == 0)
	{
		const auto address = get_vdf_reward_winner(block);
		if(block->vdf_reward_payout != address) {
			throw std::logic_error("invalid vdf_reward_payout");
		}
	} else {
		if(block->vdf_reward_payout) {
			throw std::logic_error("invalid vdf_reward_payout (must be null)");
		}
	}

	if(block->height % params->reward_adjust_interval == 0)
	{
		const auto base_reward = calc_new_base_reward(params, prev);
		if(block->base_reward != base_reward) {
			throw std::logic_error("invalid base_reward: " + std::to_string(block->base_reward) + " != " + std::to_string(base_reward));
		}
		if(block->reward_vote_sum != block->reward_vote) {
			throw std::logic_error("invalid reward_vote_sum");
		}
		if(block->reward_vote_count != (block->reward_vote ? 1 : 0)) {
			throw std::logic_error("invalid reward_vote_count");
		}
	} else {
		if(block->base_reward != prev->base_reward) {
			throw std::logic_error("invalid base_reward");
		}
		if(block->reward_vote_sum != prev->reward_vote_sum + block->reward_vote) {
			throw std::logic_error("invalid reward_vote_sum");
		}
		if(block->reward_vote_count != prev->reward_vote_count + (block->reward_vote ? 1 : 0)) {
			throw std::logic_error("invalid reward_vote_count");
		}
	}

	if(block->height < params->transaction_activation && block->tx_count) {
		throw std::logic_error("transactions not activated yet");
	}
	if(block->project_addr != prev->project_addr) {
		throw std::logic_error("invalid project_addr");
	}

	{
		std::set<std::pair<addr_t, addr_t>> keys;
		for(const auto& tx : block->tx_list) {
			if(tx->sender) {
				keys.emplace(*tx->sender, addr_t());
			}
			for(const auto& in : tx->inputs) {
				keys.emplace(in.address, in.contract);
			}
		}
		prefetch_balances(keys);
	}

	auto context = new_exec_context(block->height);
	{
		std::unordered_set<addr_t> tx_set;
		tx_set.reserve(block->tx_count);

		balance_cache_t balance_cache(&balance_table);

		std::shared_ptr<const Transaction> prev;

		for(const auto& tx : block->tx_list) {
			if(!tx) {
				throw std::logic_error("null transaction");
			}
			if(!tx->sender) {
				throw std::logic_error("transaction missing sender");
			}
			if(!tx->exec_result) {
				throw std::logic_error("transaction missing exec_result");
			}
			if(!tx_set.insert(tx->id).second) {
				throw std::logic_error("duplicate transaction in same block");
			}
			if(prev) {
				if(tx->fee_ratio > prev->fee_ratio) {
					throw std::logic_error("invalid tx order (fee_ratio)");
				}
			}
			{
				// subtract tx fee
				const auto balance = balance_cache.find(*tx->sender, addr_t());
				const auto total_fee = tx->exec_result->total_fee;
				if(!balance || total_fee > *balance) {
					throw std::logic_error("insufficient funds to cover transaction fee");
				}
				*balance -= total_fee;
			}
			if(!tx->exec_result->did_fail) {
				// Note: exec_inputs are checked during tx validation
				for(const auto& in : tx->inputs) {
					const auto balance = balance_cache.find(in.address, in.contract);
					if(!balance || in.amount > *balance) {
						throw std::logic_error("insufficient funds to cover input");
					}
					*balance -= in.amount;
				}
			}
			prepare_context(context, tx);
			prev = tx;
		}
	}
	// minimum fee_ratio depending on block size
	{
		const uint32_t N = params->min_fee_ratio.size();
		if(N) {
			uint64_t i = 0;
			uint64_t total_size = 0;
			for(auto iter = block->tx_list.rbegin(); iter != block->tx_list.rend(); ++iter)
			{
				const auto& tx = *iter;				// tx == nullptr already checked above
				total_size += tx->static_cost;

				while(total_size > ((i + 1) * params->max_block_size) / N) {
					i++;
				}
				if(i >= N) {
					throw std::logic_error("block size overflow");
				}
				const auto min_ratio = params->min_fee_ratio[i] * 1024;
				if(tx->fee_ratio < min_ratio) {
					throw std::logic_error("transaction fee_ratio too small: " + std::to_string(tx->fee_ratio) + " < " + std::to_string(min_ratio));
				}
			}
		}
	}
	hash_t failed_tx;
	std::mutex mutex;
	std::exception_ptr failed_ex;

	for(const auto& tx : block->tx_list) {
		threads->add_task([this, tx, context, &mutex, &failed_tx, &failed_ex]() {
			context->wait(tx->id);
			try {
				if(validate(tx, context)) {
					throw std::logic_error("missing exec_result");
				}
			} catch(...) {
				std::lock_guard<std::mutex> lock(mutex);
				failed_tx = tx->id;
				failed_ex = std::current_exception();
			}
			context->signal(tx->id);
		});
	}
	threads->sync();

	if(failed_ex) {
		try {
			std::rethrow_exception(failed_ex);
		} catch(const std::exception& ex) {
			throw std::logic_error(std::string(ex.what()) + " (" + failed_tx.to_string() + ")");
		}
	}
	if(block->reward_addr) {
		const auto amount = calc_block_reward(block, block->tx_fees);
		if(block->reward_amount != amount) {
			throw std::logic_error("invalid reward_amount: "
					+ std::to_string(block->reward_amount) + " != " + std::to_string(amount));
		}
	} else {
		if(block->reward_amount) {
			throw std::logic_error("invalid reward_amount");
		}
	}
	return context;
}

exec_result_t Node::validate(std::shared_ptr<const Transaction> tx) const
{
	if(tx->exec_result) {
		throw std::logic_error("exec_result not null");
	}
	const auto height = get_height() + 1;

	if(height < params->transaction_activation) {
		throw std::logic_error("transactions not live yet");
	}
	auto context = new_exec_context(height);
	context->do_profile = exec_profile;
	context->do_trace = exec_trace;
	prepare_context(context, tx);

	const auto result = validate(tx, context);
	if(!result) {
		throw std::logic_error("!result");
	}
	return *result;
}

void Node::execute(	std::shared_ptr<const Transaction> tx,
					std::shared_ptr<const execution_context_t> context,
					std::shared_ptr<const operation::Execute> op,
					std::shared_ptr<const Contract> contract,
					const addr_t& address,
					std::vector<txout_t>& exec_outputs,
					std::map<std::pair<addr_t, addr_t>, uint128>& exec_spend_map,
					std::shared_ptr<vm::StorageCache> storage_cache,
					uint64_t& tx_cost, exec_error_t& error, const bool is_init) const
{
	auto executable = std::dynamic_pointer_cast<const contract::Executable>(contract);
	if(!executable) {
		throw std::logic_error("not an executable: " + address.to_string());
	}
	auto engine = std::make_shared<vm::Engine>(address, storage_cache, false);
	engine->do_profile = context->do_profile;
	engine->do_trace = context->do_trace;
	{
		const auto avail_gas = fee_to_cost<mmx::static_failure>(tx->max_fee_amount, tx->fee_ratio);
		engine->gas_limit = std::min(avail_gas - std::min(tx_cost, avail_gas), params->max_tx_cost);
	}
	if(op->user) {
		const auto contract = get_contract_for_ex(*op->user, &engine->gas_used, engine->gas_limit);
		contract->validate(tx->get_solution(op->solution), tx->id);

		engine->write(vm::MEM_EXTERN + vm::EXTERN_USER, vm::to_binary(*op->user));
	} else {
		engine->write(vm::MEM_EXTERN + vm::EXTERN_USER, vm::var_t());
	}
	engine->write(vm::MEM_EXTERN + vm::EXTERN_ADDRESS, vm::to_binary(address));
	engine->write(vm::MEM_EXTERN + vm::EXTERN_NETWORK, vm::to_binary(params->network));

	if(auto deposit = std::dynamic_pointer_cast<const operation::Deposit>(op)) {
		{
			uint128 amount = deposit->amount;
			if(auto value = storage_cache->get_balance(address, deposit->currency)) {
				amount += *value;
			}
			storage_cache->set_balance(address, deposit->currency, amount);
		}
		vm::set_deposit(engine, deposit->currency, deposit->amount);
	}
	vm::set_args(engine, op->args);

	std::exception_ptr failed_ex;
	try {
		execute(tx, context, executable, exec_outputs, exec_spend_map, storage_cache, engine, op->method, error, is_init);
	} catch(...) {
		failed_ex = std::current_exception();
	}
	// decouple gas checking from consensus by clamping cost to limit
	tx_cost += std::min(engine->gas_used, engine->gas_limit);

	if(engine->do_profile) {
		std::ofstream out("profile_" + executable->binary.to_string() + "_" + op->method + "_" + std::to_string(get_time_us()) + ".json");
		out << vnx::to_pretty_string(engine->cost_map);
	}
	if(engine->do_trace) {
		std::ofstream out("trace_" + executable->binary.to_string() + "_" + op->method + "_" + std::to_string(get_time_us()) + ".json");
		for(const auto& t : engine->storage->trace) {
			out << t.type << "\taddr = 0x" << vnx::to_hex_string(t.addr)
					<< "\tkey = 0x" << vnx::to_hex_string(t.key) << "\tvalue = " << to_string(t.value) << std::endl;
		}
	}
	if(failed_ex) {
		std::rethrow_exception(failed_ex);
	}
}

void Node::execute(	std::shared_ptr<const Transaction> tx,
					std::shared_ptr<const execution_context_t> context,
					std::shared_ptr<const contract::Executable> executable,
					std::vector<txout_t>& exec_outputs,
					std::map<std::pair<addr_t, addr_t>, uint128>& exec_spend_map,
					std::shared_ptr<vm::StorageCache> storage_cache,
					std::shared_ptr<vm::Engine> engine,
					const std::string& method_name,
					exec_error_t& error, const bool is_init) const
{
	{
		auto iter = context->mutate_map.find(engine->contract);
		if(iter == context->mutate_map.end()) {
			throw std::logic_error("contract not locked");
		}
		const auto& list = iter->second;
		if(std::find(list.begin(), list.end(), tx->id) == list.end()) {
			throw std::logic_error("transaction did not lock contract: " + engine->contract.to_string());
		}
	}
	const auto binary = get_contract_as<contract::Binary>(executable->binary, &engine->gas_used, engine->gas_limit);
	if(!binary) {
		throw std::logic_error("no such binary: " + executable->binary.to_string());
	}
	auto method = vm::find_method(binary, method_name);
	if(!method) {
		throw std::logic_error("no such method: " + method_name);
	}
	if(is_init) {
		if(!method->is_init) {
			throw std::logic_error("not a constructor: " + method_name);
		}
	} else {
		if(!method->is_public) {
			throw std::logic_error("method is not public: " + method_name);
		}
	}
	vm::load(engine, binary);

	std::map<addr_t, std::shared_ptr<const Contract>> contract_cache;
	contract_cache[tx->id] = tx->deploy;

	engine->remote_call = [this, tx, context, executable, storage_cache, &engine, &contract_cache, &exec_outputs, &exec_spend_map, &error]
		(const std::string& name, const std::string& method, const uint32_t nargs)
	{
		const auto address = executable->get_external(name);

		auto& fetch = contract_cache[address];
		if(!fetch) {
			fetch = get_contract_ex(address, &engine->gas_used, engine->gas_limit);
		}
		const auto contract = std::dynamic_pointer_cast<const contract::Executable>(fetch);
		if(!contract) {
			throw std::logic_error("not an executable: " + address.to_string());
		}
		engine->gas_used += params->min_txfee_exec;
		engine->check_gas();

		const auto child = std::make_shared<vm::Engine>(address, storage_cache, false);
		child->gas_limit = engine->gas_limit - std::min(engine->gas_used, engine->gas_limit);

		const auto stack_ptr = engine->get_stack_ptr();
		for(uint32_t i = 0; i < nargs; ++i) {
			vm::copy(child, engine, vm::MEM_STACK + 1 + i, stack_ptr + 1 + i);
		}
		child->write(vm::MEM_EXTERN + vm::EXTERN_USER, vm::to_binary(engine->contract));
		child->write(vm::MEM_EXTERN + vm::EXTERN_ADDRESS, vm::to_binary(address));
		child->write(vm::MEM_EXTERN + vm::EXTERN_NETWORK, vm::to_binary(params->network));

		execute(tx, context, contract, exec_outputs, exec_spend_map, storage_cache, child, method, error, false);

		vm::copy(engine, child, stack_ptr, vm::MEM_STACK);

		engine->gas_used += child->gas_used;
		engine->check_gas();
	};

	engine->read_contract = [this, tx, executable, &engine, &contract_cache]
		(const addr_t& address, const std::string& field, const uint64_t dst)
	{
		auto& contract = contract_cache[address];
		if(!contract) {
			contract = get_contract_ex(address, &engine->gas_used, engine->gas_limit);
		}
		if(!contract) {
			throw std::logic_error("no such contract: " + address.to_string());
		}
		vm::assign(engine, dst, contract->read_field(field));
		engine->check_gas();
	};

	engine->write(vm::MEM_EXTERN + vm::EXTERN_HEIGHT, vm::uint_t(context->height));
	engine->write(vm::MEM_EXTERN + vm::EXTERN_TXID, vm::to_binary(tx->id));

	try {
		vm::execute(engine, *method, true);
	} catch(...) {
		error.code = engine->error_code;
		error.address = engine->error_addr;

		if(auto line = binary->find_line(error.address)) {
			error.line = *line;
		}
		if(exec_debug) {
			engine->dump_memory();
		}
		throw;
	}

	for(const auto& out : engine->outputs) {
		{
			auto amount = storage_cache->get_balance(engine->contract, out.contract);
			if(!amount || out.amount > *amount) {
				throw std::logic_error("contract over-spend");
			}
			*amount -= out.amount;
			storage_cache->set_balance(engine->contract, out.contract, *amount);
		}
		exec_outputs.push_back(out);
		exec_spend_map[std::make_pair(engine->contract, out.contract)] += out.amount;
	}
	exec_outputs.insert(exec_outputs.end(), engine->mint_outputs.begin(), engine->mint_outputs.end());
}

std::shared_ptr<const exec_result_t>
Node::validate(	std::shared_ptr<const Transaction> tx,
				std::shared_ptr<const execution_context_t> context) const
{
	if(!tx->is_valid(params)) {
		throw mmx::static_failure("invalid tx");
	}
	if(tx->static_cost > params->max_tx_cost) {
		throw mmx::static_failure("static_cost > max_tx_cost");
	}
	if(uint64_t(tx->max_fee_amount) >> 32) {
		throw mmx::static_failure("max fee amount >= 2^32");
	}
	if(tx_index.count(tx->id)) {
		throw mmx::static_failure("duplicate tx");
	}
	const uint64_t gas_limit = std::min(
			fee_to_cost<mmx::static_failure>(tx->max_fee_amount, tx->fee_ratio), params->max_tx_cost);
	const uint64_t static_fee = cost_to_fee<mmx::static_failure>(tx->static_cost, tx->fee_ratio);

	uint64_t tx_cost = tx->static_cost;
	std::vector<txin_t> exec_inputs;
	std::vector<txout_t> exec_outputs;
	balance_cache_t balance_cache(&balance_table);
	auto storage_cache = std::make_shared<vm::StorageCache>(context->storage);
	std::unordered_map<addr_t, uint128> amounts;
	std::map<std::pair<addr_t, addr_t>, uint128> deposit_map;
	std::map<std::pair<addr_t, addr_t>, uint128> exec_spend_map;
	std::exception_ptr failed_ex;
	exec_error_t error;

	if(static_fee > tx->max_fee_amount) {
		throw mmx::static_failure("static transaction fee > max_fee_amount: "
				+ std::to_string(static_fee) + " > " + std::to_string(tx->max_fee_amount));
	}
	if(!tx->sender) {
		throw mmx::static_failure("missing transaction sender");
	}
	if(tx->solutions.empty()) {
		throw mmx::static_failure("missing sender signature");
	}
	{
		// validate tx sender
		auto pubkey = contract::PubKey::create();
		pubkey->address = *tx->sender;
		pubkey->validate(tx->solutions[0], tx->id);
	}

	const auto balance = balance_cache.find(*tx->sender, addr_t());
	if(!balance || static_fee > *balance) {
		error.code = error_code_e::INSUFFICIENT_FUNDS_TXFEE;
		throw mmx::static_failure("insufficient funds for transaction fee: "
				+ std::to_string(static_fee) + " > " + (balance ? balance->str(10) : "0"));
	}
	*balance -= static_fee;

	try {
		if(tx->expires < context->height) {
			error.code = error_code_e::TX_EXPIRED;
			throw std::logic_error("transaction expired at height " + std::to_string(tx->expires));
		}
		error.address = 0;

		for(const auto& in : tx->inputs)
		{
			const auto balance = balance_cache.find(in.address, in.contract);
			if(!balance || in.amount > *balance) {
				error.code = error_code_e::INSUFFICIENT_FUNDS;
				throw std::logic_error("insufficient funds for " + in.address.to_string());
			}
			const auto solution = tx->get_solution(in.solution);
			if(!solution) {
				throw mmx::invalid_solution("missing solution");
			}
			std::shared_ptr<const Contract> contract;

			if(in.flags & txin_t::IS_EXEC) {
				contract = get_contract_ex(in.address, &tx_cost, gas_limit);
			} else {
				auto pubkey = contract::PubKey::create();
				pubkey->address = in.address;
				contract = pubkey;
			}
			if(!contract) {
				throw std::logic_error("no such contract: " + in.address.to_string());
			}
			contract->validate(solution, tx->id);

			*balance -= in.amount;
			amounts[in.contract] += in.amount;
			error.address++;
		}
		error.address = 0;

		for(const auto& out : tx->outputs)
		{
			if(out.amount == 0) {
				throw std::logic_error("zero amount output");
			}
			auto& value = amounts[out.contract];
			if(out.amount > value) {
				throw std::logic_error("transaction over-spend");
			}
			value -= out.amount;
			error.address++;
		}
		error.address = -1;

		if(tx->deploy)
		{
			if(!tx->deploy->is_valid()) {
				error.code = error_code_e::INVALID_CONTRACT;
				throw std::logic_error("invalid contract");
			}

			if(auto exec = std::dynamic_pointer_cast<const contract::Executable>(tx->deploy))
			{
				// make sure all dependencies exist (prevent limit bypass)
				for(const auto& entry : exec->depends) {
					if(!tx_index.count(entry.second)) {
						error.code = error_code_e::INVALID_CONTRACT;
						throw std::logic_error("missing dependency: " + entry.first);
					}
				}
				auto op = operation::Execute::create();
				op->method = exec->init_method;
				op->args = exec->init_args;
				execute(tx, context, op, exec, tx->id, exec_outputs, exec_spend_map, storage_cache, tx_cost, error, true);
			}
		}
		error.operation = 0;

		for(const auto& op : tx->get_operations())
		{
			if(!op || !op->is_valid()) {
				error.code = error_code_e::INVALID_OPERATION;
				throw std::logic_error("invalid operation");
			}
			const auto address = (op->address == addr_t() ? addr_t(tx->id) : op->address);
			const auto contract = (address == tx->id ? tx->deploy : get_contract_ex(address, &tx_cost, gas_limit));
			if(!contract) {
				throw std::logic_error("no such contract: " + address.to_string());
			}

			if(auto deposit = std::dynamic_pointer_cast<const operation::Deposit>(op))
			{
				auto& value = amounts[deposit->currency];
				if(deposit->amount > value) {
					throw std::logic_error("deposit over-spend");
				}
				value -= deposit->amount;

				deposit_map[std::make_pair(address, deposit->currency)] += deposit->amount;
			}
			if(auto exec = std::dynamic_pointer_cast<const operation::Execute>(op))
			{
				const auto solution = tx->get_solution(op->solution);
				execute(tx, context, exec, contract, address, exec_outputs, exec_spend_map, storage_cache, tx_cost, error, false);
			}
			error.operation++;
		}
		error.operation = -1;

		// create exec inputs
		for(const auto& entry : exec_spend_map) {
			auto amount_left = entry.second;
			{
				// use deposit amounts first
				auto& deposit = deposit_map[entry.first];
				const auto amount = std::min(deposit, amount_left);
				deposit -= amount;
				amount_left -= amount;
			}
			if(amount_left) {
				txin_t in;
				in.address = entry.first.first;
				in.contract = entry.first.second;
				in.amount = amount_left;
				exec_inputs.push_back(in);
			}
		}

		// create deposit outputs
		for(const auto& entry : deposit_map) {
			if(const auto& amount = entry.second) {
				txout_t out;
				out.address = entry.first.first;
				out.contract = entry.first.second;
				out.amount = amount;
				exec_outputs.push_back(out);
			}
		}

		// check for left-over amounts
		for(const auto& entry : amounts) {
			if(entry.second) {
				if(!tx->deploy) {
					throw std::logic_error("implicit deposit without deploy");
				}
				if(const auto& amount = entry.second) {
					txout_t out;
					out.address = tx->id;
					out.contract = entry.first;
					out.amount = amount;
					exec_outputs.push_back(out);
				}
			}
		}

		if(!tx->exec_result) {
			for(const auto& in: exec_inputs) {
				tx_cost += in.calc_cost(params);
			}
			for(const auto& out: exec_outputs) {
				tx_cost += out.calc_cost(params);
			}
		}
		if(tx_cost > params->max_tx_cost) {
			throw mmx::static_failure("transaction cost > max_tx_cost");
		}
		if(tx_cost >> 32) {
			throw mmx::static_failure("transaction cost >= 2^32");
		}
	} catch(const mmx::static_failure& ex) {
		throw;
	} catch(...) {
		failed_ex = std::current_exception();
	}
	uint64_t tx_fee = 0;

	try {
		const auto total_fee = cost_to_fee<mmx::static_failure>(tx_cost, tx->fee_ratio);

		tx_fee = std::min<uint64_t>(total_fee, tx->max_fee_amount);

		const auto dynamic_fee = tx_fee - static_fee;
		const auto balance = balance_cache.find(*tx->sender, addr_t());
		if(!balance || dynamic_fee > *balance) {
			error.code = error_code_e::INSUFFICIENT_FUNDS_TXFEE;
			throw mmx::static_failure("insufficient funds for transaction fee: "
					+ std::to_string(dynamic_fee) + " > " + (balance ? balance->str(10) : "0"));
		}
		*balance -= dynamic_fee;

		if(total_fee > tx->max_fee_amount && !failed_ex) {
			error.code = error_code_e::TXFEE_OVERRUN;
			throw std::logic_error("transaction fee > max_fee_amount: " + std::to_string(total_fee) + " > " + std::to_string(tx->max_fee_amount));
		}
	} catch(const mmx::static_failure& ex) {
		throw;
	} catch(...) {
		failed_ex = std::current_exception();
	}
	std::shared_ptr<exec_result_t> out;

	if(auto result = tx->exec_result) {
		if(!result->did_fail && failed_ex) {
			try {
				std::rethrow_exception(failed_ex);
			} catch(const std::exception& ex) {
				throw std::logic_error("unexpected execution failure: " + std::string(ex.what()));
			} catch(...) {
				throw std::logic_error("unexpected execution failure");
			}
		}
		if(result->did_fail && !failed_ex) {
			if(result->error) {
				throw std::logic_error("expected execution failure: " + result->error->message);
			} else {
				throw std::logic_error("expected execution failure");
			}
		}
		if(result->total_cost != tx_cost) {
			throw std::logic_error("transaction cost mismatch: "
					+ std::to_string(result->total_cost) + " != " + std::to_string(tx_cost));
		}
		if(result->total_fee != tx_fee) {
			throw std::logic_error("transaction fee mismatch: "
					+ std::to_string(result->total_fee) + " != " + std::to_string(tx_fee));
		}
		if(result->did_fail) {
			if(result->inputs.size() || result->outputs.size()) {
				throw std::logic_error("failed transaction cannot have execution inputs / outputs");
			}
		} else {
			if(result->inputs.size() != exec_inputs.size()) {
				throw std::logic_error("execution input count mismatch: "
						+ std::to_string(result->inputs.size()) + " != " + std::to_string(exec_inputs.size()));
			}
			if(result->outputs.size() != exec_outputs.size()) {
				throw std::logic_error("execution output count mismatch: "
						+ std::to_string(result->outputs.size()) + " != " + std::to_string(exec_outputs.size()));
			}
			for(size_t i = 0; i < exec_inputs.size(); ++i) {
				const auto& lhs = exec_inputs[i];
				const auto& rhs = result->inputs[i];
				if(lhs.contract != rhs.contract || lhs.address != rhs.address || lhs.amount != rhs.amount || lhs.memo != rhs.memo || lhs.flags != rhs.flags) {
					throw std::logic_error("execution input mismatch at index " + std::to_string(i));
				}
			}
			for(size_t i = 0; i < exec_outputs.size(); ++i) {
				const auto& lhs = exec_outputs[i];
				const auto& rhs = result->outputs[i];
				if(lhs.contract != rhs.contract || lhs.address != rhs.address || lhs.amount != rhs.amount || lhs.memo != rhs.memo) {
					throw std::logic_error("execution output mismatch at index " + std::to_string(i));
				}
			}
		}
		if(result->error) {
			if(result->error->code != error.code) {
				throw std::logic_error("error code mismatch");
			}
			if(result->error->address != error.address) {
				throw std::logic_error("error address mismatch");
			}
			if(result->error->operation != error.operation) {
				throw std::logic_error("error operation mismatch");
			}
			// Note: error line and message are not enforced by consensus
			// Note: message length already checked in is_valid()
		} else if(result->did_fail) {
			throw std::logic_error("missing error information");
		}
	} else {
		out = std::make_shared<exec_result_t>();
		out->total_cost = tx_cost;
		out->total_fee = tx_fee;

		if(failed_ex) {
			try {
				std::rethrow_exception(failed_ex);
			} catch(const std::exception& ex) {
				std::string msg = ex.what();
				msg.resize(std::min<size_t>(msg.size(), exec_error_t::MAX_MESSAGE_LENGTH));
				error.message = msg;
			}
			out->error = error;
			out->did_fail = true;
		} else {
			out->inputs = exec_inputs;
			out->outputs = exec_outputs;
		}
	}

	if(!failed_ex) {
		storage_cache->commit();
	}
	return out;
}

void Node::validate_diff_adjust(const uint64_t& block, const uint64_t& prev) const
{
	const auto max_update = std::max<uint64_t>(prev >> params->max_diff_adjust, 1);
	if(block > prev && block - prev > max_update) {
		throw std::logic_error("invalid difficulty adjustment upwards");
	}
	if(prev > block && prev - block > max_update) {
		throw std::logic_error("invalid difficulty adjustment downwards");
	}
}


} // mmx
