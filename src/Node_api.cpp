/*
 * Node_api.cpp
 *
 *  Created on: Jun 30, 2024
 *      Author: mad
 */

#include <mmx/Node.h>
#include <mmx/contract/PubKey.hxx>
#include <mmx/contract/Executable.hxx>
#include <mmx/ProofOfSpaceNFT.hxx>
#include <mmx/tx_entry_t.hpp>
#include <mmx/vm/Engine.h>
#include <mmx/vm_interface.h>
#include <mmx/helpers.h>

#include <mmx/Node_get_block.hxx>
#include <mmx/Node_get_block_at.hxx>
#include <mmx/Node_get_header.hxx>
#include <mmx/Node_get_header_at.hxx>
#include <mmx/Node_get_tx_ids.hxx>
#include <mmx/Node_get_tx_ids_at.hxx>
#include <mmx/Node_get_tx_ids_since.hxx>
#include <mmx/Node_get_tx_height.hxx>
#include <mmx/Node_get_tx_info.hxx>
#include <mmx/Node_get_tx_info_for.hxx>
#include <mmx/Node_get_transaction.hxx>
#include <mmx/Node_get_transactions.hxx>
#include <mmx/Node_get_history.hxx>
#include <mmx/Node_get_history_memo.hxx>
#include <mmx/Node_get_contract.hxx>
#include <mmx/Node_get_contract_for.hxx>
#include <mmx/Node_get_contracts.hxx>
#include <mmx/Node_get_contracts_by.hxx>
#include <mmx/Node_get_contracts_owned_by.hxx>
#include <mmx/Node_get_balance.hxx>
#include <mmx/Node_get_total_balance.hxx>
#include <mmx/Node_get_balances.hxx>
#include <mmx/Node_get_contract_balances.hxx>
#include <mmx/Node_get_total_balances.hxx>
#include <mmx/Node_get_all_balances.hxx>
#include <mmx/Node_get_exec_history.hxx>
#include <mmx/Node_read_storage.hxx>
#include <mmx/Node_dump_storage.hxx>
#include <mmx/Node_read_storage_var.hxx>
#include <mmx/Node_read_storage_entry_var.hxx>
#include <mmx/Node_read_storage_field.hxx>
#include <mmx/Node_read_storage_entry_addr.hxx>
#include <mmx/Node_read_storage_entry_string.hxx>
#include <mmx/Node_read_storage_array.hxx>
#include <mmx/Node_read_storage_map.hxx>
#include <mmx/Node_read_storage_object.hxx>
#include <mmx/Node_call_contract.hxx>
#include <mmx/Node_get_total_supply.hxx>
#include <mmx/Node_get_offer.hxx>
#include <mmx/Node_fetch_offers.hxx>
#include <mmx/Node_get_offers.hxx>
#include <mmx/Node_get_offers_by.hxx>
#include <mmx/Node_get_recent_offers.hxx>
#include <mmx/Node_get_recent_offers_for.hxx>
#include <mmx/Node_get_trade_history.hxx>
#include <mmx/Node_get_trade_history_for.hxx>
#include <mmx/Node_get_swaps.hxx>
#include <mmx/Node_get_swap_info.hxx>
#include <mmx/Node_get_swap_user_info.hxx>
#include <mmx/Node_get_swap_history.hxx>
#include <mmx/Node_get_swap_trade_estimate.hxx>
#include <mmx/Node_get_swap_fees_earned.hxx>
#include <mmx/Node_get_swap_equivalent_liquidity.hxx>
#include <mmx/Node_get_swap_liquidity_by.hxx>
#include <mmx/Node_get_farmed_blocks.hxx>
#include <mmx/Node_get_farmer_ranking.hxx>
#include <mmx/Node_get_farmed_block_summary.hxx>
#include <mmx/Node_get_plot_nft_info.hxx>
#include <mmx/Node_get_plot_nft_target.hxx>
#include <mmx/Node_validate.hxx>
#include <mmx/Node_verify_plot_nft_target.hxx>
#include <mmx/Node_verify_partial.hxx>
#include <mmx/Node_get_vdf_peak.hxx>
#include <mmx/Node_get_vdf_height.hxx>

#include <vnx/vnx.h>
#include <vnx/InternalError.hxx>

#include <shared_mutex>


namespace mmx {

std::shared_ptr<const ChainParams> Node::get_params() const {
	return params;
}

std::shared_ptr<const NetworkInfo> Node::get_network_info() const
{
	if(const auto peak = get_peak()) {
		if(!network || peak->height != network->height || is_synced != network->is_synced)
		{
			auto info = NetworkInfo::create();
			info->is_synced = is_synced;
			info->height = peak->height;
			info->vdf_height = peak->vdf_height;
			info->time_stamp = peak->time_stamp;
			info->synced_since = synced_since;
			info->name = params->network;
			info->node_version = node_version;
			info->node_commit = node_commit;
			info->time_diff = peak->time_diff;
			info->space_diff = peak->space_diff;
			info->vdf_speed = get_vdf_speed(params, peak->time_diff) / 1e6;
			const auto avg_txfee = calc_min_reward_deduction(params, peak->txfee_buffer);
			info->block_reward = (peak->height >= params->reward_activation ?
					(peak->base_reward + std::max<int64_t>(params->min_reward - avg_txfee, 0)) : 0);
			info->total_space = calc_total_netspace(params, peak->space_diff) / 1000 / 1000 / 1000;
			info->total_supply = get_total_supply(addr_t());
			info->address_count = mmx_address_count;
			info->genesis_hash = get_genesis_hash();
			info->average_txfee = avg_txfee;
			{
				size_t num_blocks = 0;
				for(const auto& fork : get_fork_line()) {
					if(fork->block->farmer_sig) {
						info->block_size += fork->block->static_cost / double(params->max_block_size);
						num_blocks++;
					}
				}
				if(num_blocks) {
					info->block_size /= num_blocks;
				}
			}
			network = info;
		}
	}
	return network;
}

hash_t Node::get_genesis_hash() const
{
	if(auto block = get_header_at(0)) {
		return block->hash;
	}
	throw std::logic_error("have no genesis");
}

uint32_t Node::get_height() const
{
	if(auto block = get_peak()) {
		return block->height;
	}
	throw std::logic_error("have no peak");
}

vnx::optional<uint32_t> Node::get_synced_height() const
{
	if(is_synced) {
		return get_height();
	}
	return nullptr;
}

vnx::optional<uint32_t> Node::get_synced_vdf_height() const
{
	if(is_synced) {
		return get_vdf_height();
	}
	return nullptr;
}

std::shared_ptr<const Block> Node::get_block(const hash_t& hash) const
{
	return std::dynamic_pointer_cast<const Block>(get_block_ex(hash, true));
}

std::shared_ptr<const BlockHeader> Node::get_block_ex(const hash_t& hash, bool full_block) const
{
	// THREAD SAFE (for concurrent reads)
	auto iter = fork_tree.find(hash);
	if(iter != fork_tree.end()) {
		return iter->second->block;
	}
	if(!full_block) {
		auto iter = history.find(hash);
		if(iter != history.end()) {
			return iter->second;
		}
	}
	block_index_t entry;
	if(block_index.find(hash, entry)) {
		vnx::File file(blocks->get_path());
		file.open("rb");
		file.seek_to(entry.file_offset);
		return read_block(file, full_block);
	}
	return nullptr;
}

std::shared_ptr<const Block> Node::get_block_at(const uint32_t& height) const
{
	return std::dynamic_pointer_cast<const Block>(get_block_at_ex(height, true));
}

std::shared_ptr<const BlockHeader> Node::get_block_at_ex(const uint32_t& height, bool full_block) const
{
	if(auto hash = get_block_hash(height)) {
		return get_block_ex(*hash, full_block);
	}
	return nullptr;
}

std::shared_ptr<const BlockHeader> Node::get_header(const hash_t& hash) const
{
	return get_block_ex(hash, false);
}

std::shared_ptr<const BlockHeader> Node::get_header_at(const uint32_t& height) const
{
	return get_block_at_ex(height, false);
}

vnx::optional<hash_t> Node::get_block_hash(const uint32_t& height) const
{
	hash_t hash;
	if(height_map.find(height, hash)) {
		return hash;
	}
	return nullptr;
}

vnx::optional<std::pair<hash_t, hash_t>> Node::get_block_hash_ex(const uint32_t& height) const
{
	if(auto hash = get_block_hash(height)) {
		block_index_t entry;
		if(block_index.find(*hash, entry)) {
			return std::make_pair(*hash, entry.content_hash);
		}
	}
	return nullptr;
}

std::vector<hash_t> Node::get_tx_ids(const uint32_t& limit) const
{
	std::vector<hash_t> out;
	tx_log.reverse_scan([&out, limit](const uint32_t&, const std::vector<hash_t>& list) -> bool {
		for(const auto& id : list) {
			if(out.size() < limit) {
				out.push_back(id);
			} else {
				return false;
			}
		}
		return out.size() < limit;
	});
	return out;
}

std::vector<hash_t> Node::get_tx_ids_at(const uint32_t& height) const
{
	std::vector<hash_t> list;
	tx_log.find(height, list);
	return list;
}

std::vector<hash_t> Node::get_tx_ids_since(const uint32_t& height) const
{
	std::vector<std::vector<hash_t>> list;
	tx_log.find_greater_equal(height, list);

	std::vector<hash_t> out;
	for(const auto& entry : list) {
		out.insert(out.end(), entry.begin(), entry.end());
	}
	return out;
}

vnx::optional<uint32_t> Node::get_tx_height(const hash_t& id) const
{
	tx_index_t entry;
	if(tx_index.find(id, entry)) {
		return entry.height;
	}
	return nullptr;
}

vnx::optional<tx_info_t> Node::get_tx_info(const hash_t& id) const
{
	if(auto tx = get_transaction(id, true)) {
		return get_tx_info_for(tx);
	}
	return nullptr;
}

vnx::optional<tx_info_t> Node::get_tx_info_for(std::shared_ptr<const Transaction> tx) const
{
	if(!tx) {
		return nullptr;
	}
	tx_info_t info;
	info.id = tx->id;
	info.expires = tx->expires;
	{
		tx_index_t entry;
		if(tx_index.find(tx->id, entry)) {
			info.height = entry.height;
			info.time_stamp = entry.time_stamp;
			info.block = get_block_hash(entry.height);
		}
	}
	if(tx->exec_result) {
		info.fee = tx->exec_result->total_fee;
		info.cost = tx->exec_result->total_cost;
		info.did_fail = tx->exec_result->did_fail;
		info.message = tx->exec_result->get_error_msg();
	} else {
		info.cost = tx->static_cost;
	}
	info.note = tx->note;
	info.sender = tx->sender;
	info.inputs = tx->get_inputs();
	info.outputs = tx->get_outputs();
	info.operations = tx->get_operations();
	info.deployed = tx->deploy;

	std::set<addr_t> contracts;
	for(const auto& in : info.inputs) {
		contracts.insert(in.contract);
		info.input_amounts[in.contract] += in.amount;
	}
	for(const auto& out : info.outputs) {
		contracts.insert(out.contract);
		info.output_amounts[out.contract] += out.amount;
	}
	for(const auto& op : tx->execute) {
		if(op) {
			contracts.insert(op->address);
		}
	}
	for(const auto& addr : contracts) {
		if(auto contract = get_contract(addr)) {
			info.contracts[addr] = contract;
		}
	}
	return info;
}

std::shared_ptr<const Transaction> Node::get_transaction(const hash_t& id, const bool& pending) const
{
	if(pending) {
		auto iter = tx_pool.find(id);
		if(iter != tx_pool.end()) {
			return iter->second.tx;
		}
		for(const auto& entry : tx_queue) {
			if(const auto& tx = entry.second) {
				if(tx->id == id) {
					return tx;
				}
			}
		}
	}
	tx_index_t entry;
	if(tx_index.find(id, entry)) {
		vnx::File file(blocks->get_path());
		file.open("rb");
		file.seek_to(entry.file_offset);
		const auto value = vnx::read(file.in);
		if(auto tx = std::dynamic_pointer_cast<const Transaction>(value)) {
			return tx;
		}
	}
	return nullptr;
}

std::vector<std::shared_ptr<const Transaction>> Node::get_transactions(const std::vector<hash_t>& ids) const
{
	std::vector<std::shared_ptr<const Transaction>> list;
	for(const auto& id : ids) {
		std::shared_ptr<const Transaction> tx;
		try {
			tx = get_transaction(id);
		} catch(...) {
			// ignore
		}
		list.push_back(tx);
	}
	return list;
}

inline bool filter_txio(const txio_entry_t& entry, const query_filter_t& filter)
{
	if(filter.type && entry.type != *filter.type) {
		return false;
	}
	if(!filter.currency.empty() && !filter.currency.count(entry.contract)) {
		return false;
	}
	return true;
}

std::vector<tx_entry_t> Node::get_history(const std::vector<addr_t>& addresses, const query_filter_t& filter) const
{
	if(const auto& memo = filter.memo) {
		return get_history_memo(addresses, *memo, filter);
	}
	std::map<addr_t, uint32_t> count_map;
	std::map<addr_t, std::tuple<addr_t, uint32_t, uint32_t>> state_map;

	const std::set<addr_t> address_set(addresses.begin(), addresses.end());
	for(const auto& address : address_set) {
		state_map[address] = std::make_tuple(address, filter.until, -1);
	}
	const uint32_t chunk_size = 100;
	const uint64_t max_search = filter.max_search ? filter.max_search : -1;

	uint64_t num_search = 0;
	std::vector<tx_entry_t> res;
	while(!state_map.empty() && num_search < max_search) {
		std::vector<addr_t> done;
		for(auto& entry : state_map) {
			const auto& address = entry.first;
			std::vector<std::pair<std::tuple<addr_t, uint32_t, uint32_t>, txio_entry_t>> entries;
			num_search += txio_log.find_last_range(
					std::make_tuple(address, filter.since, 0), entry.second, entries, chunk_size);

			auto& count = count_map[address];
			for(const auto& entry : entries) {
				if(filter_txio(entry.second, filter)) {
					res.push_back(tx_entry_t::create_ex(entry.second));
					count++;
				}
			}
			if(entries.size()) {
				entry.second = entries.back().first;
			}
			if(entries.size() < chunk_size || count >= uint32_t(filter.limit)) {
				done.push_back(address);
			}
		}
		for(const auto& address : done) {
			// add remaining entries for last block
			auto end = state_map[address];
			auto begin = end;
			std::get<2>(begin) = 0;
			std::vector<txio_entry_t> more;
			num_search += txio_log.find_last_range(begin, end, more, -1);
			for(const auto& entry : more) {
				if(filter_txio(entry, filter)) {
					res.push_back(tx_entry_t::create_ex(entry));
				}
			}
			state_map.erase(address);
		}
	}

	if(filter.with_pending) {
		std::lock_guard<std::mutex> lock(mutex);
		for(const auto& address : address_set) {
			const auto begin = tx_pool_index.lower_bound(std::make_pair(address, hash_t()));
			const auto end = tx_pool_index.upper_bound(std::make_pair(address, hash_t::ones()));
			for(auto iter = begin; iter != end; ++iter) {
				if(auto tx = iter->second) {
					for(const auto& in : tx->get_inputs()) {
						if(address_set.count(in.address)) {
							tx_entry_t entry;
							entry.txio_t::operator=(in);
							entry.type = tx_type_e::SPEND;
							entry.txid = tx->id;
							entry.height = -1;
							entry.is_pending = true;
							res.push_back(entry);
						}
					}
					for(const auto& out : tx->get_outputs()) {
						if(address_set.count(out.address)) {
							tx_entry_t entry;
							entry.txio_t::operator=(out);
							entry.type = tx_type_e::RECEIVE;
							entry.txid = tx->id;
							entry.height = -1;
							entry.is_pending = true;
							res.push_back(entry);
						}
					}
				}
			}
		}
	}
	std::sort(res.begin(), res.end(), [](const tx_entry_t& L, const tx_entry_t& R) -> bool {
		return std::make_tuple(L.height, L.txid, L.type, L.contract, L.address, L.memo, L.amount) >
			   std::make_tuple(R.height, R.txid, R.type, R.contract, R.address, R.memo, R.amount);
	});
	if(filter.limit >= 0 && res.size() > size_t(filter.limit)) {
		size_t i = filter.limit;
		for(const auto cutoff = res[i].height; i < res.size() && res[i].height == cutoff; ++i);
		res.resize(i);
	}
	return res;
}

std::vector<tx_entry_t> Node::get_history_memo(const std::vector<addr_t>& addresses, const std::string& memo, const query_filter_t& filter) const
{
	std::map<addr_t, uint32_t> count_map;
	std::map<addr_t, std::tuple<hash_t, uint32_t, uint32_t>> state_map;

	const std::set<addr_t> address_set(addresses.begin(), addresses.end());
	for(const auto& address : address_set) {
		state_map[address] = std::make_tuple(hash_t(address + memo), filter.until, -1);
	}
	const uint32_t chunk_size = 100;
	const uint64_t max_search = filter.max_search ? filter.max_search : -1;

	uint64_t num_search = 0;
	std::vector<tx_entry_t> res;
	while(!state_map.empty() && num_search < max_search) {
		std::vector<addr_t> done;
		for(auto& entry : state_map) {
			const auto& address = entry.first;
			const auto& key = std::get<0>(entry.second);

			std::vector<std::pair<std::tuple<hash_t, uint32_t, uint32_t>, addr_t>> entries;
			num_search += memo_log.find_last_range(std::make_tuple(key, filter.since, 0), entry.second, entries, chunk_size);

			auto& count = count_map[address];
			for(const auto& index : entries) {
				txio_entry_t entry;
				if(txio_log.find(std::make_tuple(index.second, std::get<1>(index.first), std::get<2>(index.first)), entry)) {
					if(filter_txio(entry, filter)) {
						res.push_back(tx_entry_t::create_ex(entry));
						count++;
					}
				}
			}
			if(entries.size()) {
				entry.second = entries.back().first;
			}
			if(entries.size() < chunk_size || count >= uint32_t(filter.limit)) {
				done.push_back(address);
			}
		}
		for(const auto& address : done) {
			state_map.erase(address);
		}
	}

	if(filter.with_pending) {
		std::lock_guard<std::mutex> lock(mutex);
		for(const auto& address : address_set) {
			const hash_t key(address + memo);
			const auto begin = tx_pool_index.lower_bound(std::make_pair(key, hash_t()));
			const auto end = tx_pool_index.upper_bound(std::make_pair(key, hash_t::ones()));
			for(auto iter = begin; iter != end; ++iter) {
				if(auto tx = iter->second) {
					for(const auto& out : tx->get_outputs()) {
						if(address_set.count(out.address) && out.memo && (*out.memo) == memo) {
							tx_entry_t entry;
							entry.txio_t::operator=(out);
							entry.type = tx_type_e::RECEIVE;
							entry.txid = tx->id;
							entry.height = -1;
							entry.is_pending = true;
							res.push_back(entry);
						}
					}
				}
			}
		}
	}
	std::sort(res.begin(), res.end(), [](const tx_entry_t& L, const tx_entry_t& R) -> bool {
		return std::make_tuple(L.height, L.txid, L.type, L.contract, L.address, L.memo, L.amount) >
			   std::make_tuple(R.height, R.txid, R.type, R.contract, R.address, R.memo, R.amount);
	});
	if(filter.limit >= 0 && res.size() > size_t(filter.limit)) {
		size_t i = filter.limit;
		for(const auto cutoff = res[i].height; i < res.size() && res[i].height == cutoff; ++i);
		res.resize(i);
	}
	return res;
}

std::shared_ptr<const Contract> Node::get_contract(const addr_t& address) const
{
	return get_contract_ex(address);
}

std::shared_ptr<const Contract> Node::get_contract_ex(const addr_t& address, uint64_t* read_cost, const uint64_t gas_limit) const
{
	if(read_cost) {
		tx_index_t index;
		tx_index.find(address, index);

		const auto cost = params->min_txfee_read + index.contract_read_cost;
		if(*read_cost + cost > gas_limit) {
			throw std::runtime_error("not enough gas to read contract");
		}
		*read_cost += cost;
	}
	std::shared_ptr<const Contract> contract;
	{
		std::lock_guard<std::mutex> lock(mutex);
		contract = find_value(contract_cache, address, nullptr);
	}
	if(!contract) {
		contract_map.find(address, contract);

		if(std::dynamic_pointer_cast<const contract::Binary>(contract))
		{
			std::lock_guard<std::mutex> lock(mutex);
			if((contract_cache.size() + 1) >> 16) {
				contract_cache.clear();
			}
			contract_cache[address] = contract;
		}
	}
	return contract;
}

std::shared_ptr<const Contract> Node::get_contract_for(const addr_t& address) const
{
	return get_contract_for_ex(address);
}

std::shared_ptr<const Contract> Node::get_contract_for_ex(const addr_t& address, uint64_t* read_cost, const uint64_t gas_limit) const
{
	if(auto contract = get_contract_ex(address, read_cost, gas_limit)) {
		return contract;
	}
	auto pubkey = contract::PubKey::create();
	pubkey->address = address;
	return pubkey;
}

std::vector<std::shared_ptr<const Contract>> Node::get_contracts(const std::vector<addr_t>& addresses) const
{
	std::vector<std::shared_ptr<const Contract>> res;
	for(const auto& addr : addresses) {
		res.push_back(get_contract(addr));
	}
	return res;
}

std::vector<addr_t> Node::get_contracts_by(const std::vector<addr_t>& addresses, const vnx::optional<hash_t>& type_hash) const
{
	std::vector<addr_t> result;
	for(const auto& address : addresses) {
		std::vector<std::pair<addr_t, hash_t>> list;
		deploy_map.find_range(std::make_tuple(address, 0, 0), std::make_tuple(address, -1, -1), list);
		for(const auto& entry : list) {
			if(!type_hash || entry.second == *type_hash) {
				result.push_back(entry.first);
			}
		}
	}
	return result;
}

std::vector<addr_t> Node::get_contracts_owned_by(const std::vector<addr_t>& addresses, const vnx::optional<hash_t>& type_hash) const
{
	std::vector<addr_t> result;
	for(const auto& address : addresses) {
		std::vector<std::pair<addr_t, hash_t>> list;
		owner_map.find_range(std::make_tuple(address, 0, 0), std::make_tuple(address, -1, -1), list);
		for(const auto& entry : list) {
			if(!type_hash || entry.second == *type_hash) {
				result.push_back(entry.first);
			}
		}
	}
	return result;
}

uint128 Node::get_balance(const addr_t& address, const addr_t& currency) const
{
	uint128 value = 0;
	balance_table.find(std::make_pair(address, currency), value);
	return value;
}

uint128 Node::get_total_balance(const std::vector<addr_t>& addresses, const addr_t& currency) const
{
	uint128 total = 0;
	for(const auto& address : std::set<addr_t>(addresses.begin(), addresses.end())) {
		total += get_balance(address, currency);
	}
	return total;
}

std::map<addr_t, uint128> Node::get_balances(const addr_t& address, const std::set<addr_t>& whitelist, const int32_t& limit) const
{
	return get_total_balances({address}, whitelist, limit);
}

std::map<addr_t, balance_t> Node::get_contract_balances(
		const addr_t& address, const std::set<addr_t>& whitelist, const int32_t& limit) const
{
	bool is_locked = false;
	if(auto exec = get_contract_as<contract::Executable>(address)) {
		if(auto bin = get_contract_as<contract::Binary>(exec->binary)) {
			const std::string method = "is_locked";
			if(vm::find_method(bin, method)) {
				is_locked = call_contract(address, method, {}).to<bool>();
			}
		}
	}
	std::map<addr_t, balance_t> out;
	for(const auto& entry : get_total_balances({address}, whitelist, limit)) {
		const auto& amount = entry.second;
		auto& balance = out[entry.first];
		if(is_locked) {
			balance.locked = amount;
		} else {
			balance.spendable = amount;
		}
		balance.total = amount;
		balance.is_validated = !whitelist.empty();
	}
	return out;
}

std::map<addr_t, uint128> Node::get_total_balances(
		const std::vector<addr_t>& addresses, const std::set<addr_t>& whitelist, const int32_t& limit) const
{
	std::map<addr_t, uint128> totals;
	for(const auto& address : std::set<addr_t>(addresses.begin(), addresses.end())) {
		if(whitelist.empty()) {
			std::vector<std::pair<std::pair<addr_t, addr_t>, uint128>> result;
			balance_table.find_range(std::make_pair(address, addr_t()), std::make_pair(address, addr_t::ones()), result, limit);
			for(const auto& entry : result) {
				if(entry.second) {
					totals[entry.first.second] += entry.second;
				}
			}
		} else {
			for(const auto& currency : whitelist) {
				uint128 balance;
				balance_table.find(std::make_pair(address, currency), balance);
				if(balance) {
					totals[currency] += balance;
				}
			}
		}
	}
	return totals;
}

std::map<std::pair<addr_t, addr_t>, uint128> Node::get_all_balances(
		const std::vector<addr_t>& addresses, const std::set<addr_t>& whitelist, const int32_t& limit) const
{
	std::map<std::pair<addr_t, addr_t>, uint128> totals;
	for(const auto& address : std::set<addr_t>(addresses.begin(), addresses.end())) {
		if(whitelist.empty()) {
			std::vector<std::pair<std::pair<addr_t, addr_t>, uint128>> result;
			balance_table.find_range(std::make_pair(address, addr_t()), std::make_pair(address, addr_t::ones()), result, limit);
			for(const auto& entry : result) {
				if(entry.second) {
					totals[entry.first] += entry.second;
				}
			}
		} else {
			for(const auto& currency : whitelist) {
				uint128 balance;
				balance_table.find(std::make_pair(address, currency), balance);
				if(balance) {
					totals[std::make_pair(address, currency)] += balance;
				}
			}
		}
	}
	return totals;
}

std::vector<exec_entry_t> Node::get_exec_history(const addr_t& address, const int32_t& limit, const vnx::bool_t& recent) const
{
	std::vector<exec_entry_t> entries;
	if(recent) {
		exec_log.find_last_range(std::make_tuple(address, 0, 0), std::make_tuple(address, -1, -1), entries, limit);
	} else {
		exec_log.find_range(std::make_tuple(address, 0, 0), std::make_tuple(address, -1, -1), entries, limit);
	}
	return entries;
}

std::map<std::string, vm::varptr_t> Node::read_storage(const addr_t& contract, const uint32_t& height) const
{
	std::map<std::string, vm::varptr_t> out;
	if(auto exec = std::dynamic_pointer_cast<const contract::Executable>(get_contract(contract))) {
		if(auto bin = std::dynamic_pointer_cast<const contract::Binary>(get_contract(exec->binary))) {
			for(const auto& entry : bin->fields) {
				if(auto var = storage->read(contract, entry.second)) {
					out[entry.first] = std::move(var);
				}
			}
		}
	}
	return out;
}

std::map<uint64_t, vm::varptr_t> Node::dump_storage(const addr_t& contract, const uint32_t& height) const
{
	const auto entries = storage->find_range(contract, vm::MEM_STATIC, -1, height);
	return std::map<uint64_t, vm::varptr_t>(entries.begin(), entries.end());
}

vm::varptr_t Node::read_storage_var(const addr_t& contract, const uint64_t& address, const uint32_t& height) const
{
	return storage->read_ex(contract, address, height);
}

vm::varptr_t Node::read_storage_entry_var(const addr_t& contract, const uint64_t& address, const uint64_t& key, const uint32_t& height) const
{
	return storage->read_ex(contract, address, key, height);
}

std::pair<vm::varptr_t, uint64_t> Node::read_storage_field(const addr_t& contract, const std::string& name, const uint32_t& height) const
{
	if(auto exec = get_contract_as<contract::Executable>(contract)) {
		if(auto bin = get_contract_as<contract::Binary>(exec->binary)) {
			if(auto addr = bin->find_field(name)) {
				return std::make_pair(read_storage_var(contract, *addr, height), *addr);
			}
		}
	}
	return {};
}

std::tuple<vm::varptr_t, uint64_t, uint64_t> Node::read_storage_entry_var(const addr_t& contract, const std::string& name, const vm::varptr_t& key, const uint32_t& height) const
{
	const auto field = read_storage_field(contract, name, height);
	if(auto var = field.first) {
		uint64_t address = field.second;
		if(var->type == vm::TYPE_REF) {
			address = vm::to_ref(var);
		}
		if(auto entry = storage->lookup(contract, key)) {
			return std::make_tuple(read_storage_entry_var(contract, address, entry, height), address, entry);
		}
	}
	return {};
}

std::tuple<vm::varptr_t, uint64_t, uint64_t> Node::read_storage_entry_addr(const addr_t& contract, const std::string& name, const addr_t& key, const uint32_t& height) const
{
	return read_storage_entry_var(contract, name, vm::to_binary(key), height);
}

std::tuple<vm::varptr_t, uint64_t, uint64_t> Node::read_storage_entry_string(const addr_t& contract, const std::string& name, const std::string& key, const uint32_t& height) const
{
	return read_storage_entry_var(contract, name, vm::to_binary(key), height);
}

std::vector<vm::varptr_t> Node::read_storage_array(const addr_t& contract, const uint64_t& address, const uint32_t& height) const
{
	return storage->read_array(contract, address, height);
}

std::map<vm::varptr_t, vm::varptr_t> Node::read_storage_map(const addr_t& contract, const uint64_t& address, const uint32_t& height) const
{
	std::map<vm::varptr_t, vm::varptr_t> out;
	if(auto exec = std::dynamic_pointer_cast<const contract::Executable>(get_contract(contract))) {
		if(auto bin = std::dynamic_pointer_cast<const contract::Binary>(get_contract(exec->binary))) {
			auto engine = std::make_shared<vm::Engine>(contract, storage, true);
			engine->gas_limit = params->max_tx_cost;
			vm::load(engine, bin);
			for(const auto& entry : storage->find_entries(contract, address, height)) {
				// need to use engine to support constant keys
				if(auto key = engine->read(entry.first)) {
					out[vm::clone(key)] = entry.second;
				}
			}
		}
	}
	return out;
}

std::map<std::string, vm::varptr_t> Node::read_storage_object(const addr_t& contract, const uint64_t& address, const uint32_t& height) const
{
	std::map<std::string, vm::varptr_t> out;
	for(const auto& entry : read_storage_map(contract, address, height)) {
		out[to_string_value(entry.first)] = entry.second;
	}
	return out;
}

vnx::Variant Node::call_contract(
		const addr_t& address, const std::string& method, const std::vector<vnx::Variant>& args,
		const vnx::optional<addr_t>& user, const vnx::optional<std::pair<addr_t, uint128>>& deposit) const
{
	// Note: consensus relevant
	if(auto exec = get_contract_as<contract::Executable>(address)) {
		if(auto bin = get_contract_as<contract::Binary>(exec->binary)) {
			auto func = vm::find_method(bin, method);
			if(!func) {
				throw std::runtime_error("no such method: " + method);
			}
			auto engine = std::make_shared<vm::Engine>(address, storage, func->is_const);
			engine->gas_limit = params->max_tx_cost;
			vm::load(engine, bin);
			engine->write(vm::MEM_EXTERN + vm::EXTERN_TXID, vm::var_t());
			engine->write(vm::MEM_EXTERN + vm::EXTERN_HEIGHT, vm::uint_t(get_height()));
			engine->write(vm::MEM_EXTERN + vm::EXTERN_ADDRESS, vm::to_binary(address));
			engine->write(vm::MEM_EXTERN + vm::EXTERN_NETWORK, vm::to_binary(params->network));
			if(user) {
				engine->write(vm::MEM_EXTERN + vm::EXTERN_USER, vm::to_binary(*user));
			} else {
				engine->write(vm::MEM_EXTERN + vm::EXTERN_USER, vm::var_t());
			}
			if(deposit) {
				vm::set_deposit(engine, deposit->first, deposit->second);
			}
			vm::set_args(engine, args);
			try {
				vm::execute(engine, *func, false);
			} catch(const std::exception& ex) {
				throw std::runtime_error("exception at 0x" + vnx::to_hex_string(engine->error_addr) + ": " + ex.what());
			}
			return vm::read(engine, vm::MEM_STACK);
		}
		throw std::runtime_error("no such binary");
	}
	throw std::runtime_error("no such contract");
}

uint128 Node::get_total_supply(const addr_t& currency) const
{
	uint128 total = 0;
	total_supply_map.find(currency, total);
	return clamped_sub(total, get_balance(addr_t(), currency));
}

vnx::optional<plot_nft_info_t> Node::get_plot_nft_info(const addr_t& address) const
{
	if(auto exec = get_contract_as<contract::Executable>(address)) {
		if(exec->binary == params->plot_nft_binary) {
			auto data = read_storage(address);
			plot_nft_info_t info;
			info.name = exec->name;
			info.owner = to_addr(data["owner"]);
			info.address = address;
			const auto& unlock_height = data["unlock_height"];
			if(unlock_height && unlock_height->type == vm::TYPE_UINT) {
				const uint32_t unlock_at = to_uint(unlock_height);
				info.unlock_height = unlock_at;
				info.is_locked = get_height() < unlock_at;
			} else {
				info.is_locked = true;
			}
			if(info.is_locked) {
				info.target = to_addr(data["target"]);
			}
			const auto server_url = data["server_url"];
			if(server_url && server_url->type == vm::TYPE_STRING) {
				info.server_url = to_string_value(server_url);
			}
			return info;
		}
	}
	return nullptr;
}

addr_t Node::get_plot_nft_target(const addr_t& address, const vnx::optional<addr_t>& farmer_addr) const
{
	// Note: consensus relevant
	if(auto exec = get_contract_as<contract::Executable>(address)) try {
		if(auto bin = get_contract_as<contract::Binary>(exec->binary)) {
			const std::string method = "mmx_reward_target";
			if(vm::find_method(bin, method)) {
				vnx::Variant arg0;
				if(farmer_addr) {
					arg0 = farmer_addr->to_string();
				}
				return call_contract(address, method, {arg0}).to<addr_t>();
			}
		}
	}
	catch(const std::exception& ex) {
		throw std::logic_error("mmx_reward_target() failed with: " + std::string(ex.what()));
	}
	return address;
}

offer_data_t Node::get_offer(const addr_t& address) const
{
	auto data = read_storage(address);
	if(data.empty()) {
		throw std::runtime_error("no such offer: " + address.to_string());
	}
	offer_data_t out;
	out.address = address;
	{
		tx_index_t entry;
		if(tx_index.find(address, entry)) {
			out.height = entry.height;
			out.time_stamp = entry.time_stamp;
		}
	}
	if(auto partner = data["partner"]) {
		if(partner->type != vm::TYPE_NIL) {
			out.partner = to_addr(partner);
		}
	}
	out.owner = to_addr(data["owner"]);
	out.bid_currency = to_addr(data["bid_currency"]);
	out.ask_currency = to_addr(data["ask_currency"]);
	out.bid_balance = get_balance(address, out.bid_currency);
	out.ask_balance = get_balance(address, out.ask_currency);
	out.inv_price = to_uint(data["inv_price"]);
	out.last_update = to_uint(data["last_update"]);
	out.price = out.get_price();
	out.ask_amount = out.get_ask_amount(out.bid_balance);
	return out;
}

int Node::get_offer_state(const addr_t& address) const
{
	if(get_balance(address, to_addr(read_storage_field(address, "bid_currency").first))) {
		return 1;
	}
	if(get_balance(address, to_addr(read_storage_field(address, "ask_currency").first))) {
		return 2;
	}
	return 0;
}

std::vector<offer_data_t> Node::fetch_offers(const std::vector<addr_t>& addresses, const vnx::bool_t& state, const vnx::bool_t& closed) const
{
	std::vector<offer_data_t> out;
	for(const auto& address : addresses) {
		const int offer_state = state ? get_offer_state(address) : -1;
		if(!state || offer_state == 1 || (closed && offer_state == 2)) {
			const auto data = get_offer(address);
			if(!data.partner && !data.is_scam()) {
				out.push_back(data);
			}
		}
	}
	return out;
}

std::vector<offer_data_t> Node::get_offers(const uint32_t& since, const vnx::bool_t& state) const
{
	std::vector<addr_t> entries;
	contract_log.find_range(std::make_tuple(params->offer_binary, since, 0), std::make_tuple(params->offer_binary, -1, -1), entries);
	return fetch_offers(entries, state);
}

std::vector<offer_data_t> Node::get_offers_by(const std::vector<addr_t>& owners, const vnx::bool_t& state) const
{
	return fetch_offers(get_contracts_owned_by(owners, params->offer_binary), state, true);
}

std::vector<offer_data_t> Node::get_recent_offers(const int32_t& limit, const vnx::bool_t& state) const
{
	std::vector<offer_data_t> result;
	std::tuple<hash_t, uint32_t, uint32_t> offer_log_end(params->offer_binary, -1, -1);
	std::tuple<hash_t, uint32_t, uint32_t> offer_log_begin(params->offer_binary, 0, 0);

	while(result.size() < size_t(limit)) {
		std::vector<std::pair<std::tuple<hash_t, uint32_t, uint32_t>, addr_t>> entries;
		if(!contract_log.find_last_range(offer_log_begin, offer_log_end, entries, std::max<size_t>(limit, 100))) {
			break;
		}
		offer_log_end = entries.back().first;

		std::vector<addr_t> list;
		for(const auto& entry : entries) {
			list.push_back(entry.second);
		}
		const auto tmp = fetch_offers(list, state);
		result.insert(result.end(), tmp.begin(), tmp.end());
	}
	result.resize(std::min(result.size(), size_t(limit)));
	return result;
}

std::vector<offer_data_t> Node::get_recent_offers_for(
		const vnx::optional<addr_t>& bid, const vnx::optional<addr_t>& ask, const uint128& min_bid, const int32_t& limit, const vnx::bool_t& state) const
{
	std::vector<offer_data_t> result;
	if(!bid && !ask) {
		result = get_recent_offers(limit, state);
	} else {
		hash_t key;
		if(bid && ask) {
			key = hash_t(*ask + *bid);
		} else if(bid) {
			key = hash_t("ANY" + *bid);
		} else if(ask) {
			key = hash_t(*ask + "ANY");
		}
		std::tuple<hash_t, uint32_t, uint32_t> search_end(key, -1, -1);
		while(result.size() < size_t(limit)) {
			std::vector<std::pair<std::tuple<hash_t, uint32_t, uint32_t>, addr_t>> list;
			if(!offer_index.find_last_range(std::make_tuple(key, 0, 0), search_end, list, limit)) {
				break;
			}
			std::vector<addr_t> addresses;
			for(const auto& entry : list) {
				addresses.push_back(entry.second);
			}
			for(const auto& entry : fetch_offers(addresses, state)) {
				if(entry.bid_balance >= min_bid) {
					result.push_back(entry);
				}
			}
			search_end = list.back().first;
		}
	}
	std::sort(result.begin(), result.end(),
		[](const offer_data_t& L, const offer_data_t& R) -> bool {
			return std::make_pair(L.height, L.address) > std::make_pair(R.height, R.address);
		});
	result.resize(std::min(result.size(), size_t(limit)));
	return result;
}

trade_entry_t Node::make_trade_entry(const uint32_t& height, const trade_log_t& log) const
{
	trade_entry_t out;
	out.height = height;
	out.time_stamp = log.time_stamp;
	out.address = log.address;
	out.txid = log.txid;
	out.ask_amount = log.ask_amount;
	out.bid_amount = log.get_bid_amount();
	out.price = log.get_price();
	out.bid_currency = to_addr(read_storage_field(log.address, "bid_currency").first);
	out.ask_currency = to_addr(read_storage_field(log.address, "ask_currency").first);
	return out;
}

std::vector<trade_entry_t> Node::get_trade_history(const int32_t& limit, const uint32_t& since) const
{
	std::vector<std::pair<std::pair<uint32_t, uint32_t>, trade_log_t>> entries;
	trade_log.find_last_range(std::make_pair(since, 0), std::make_pair(-1, -1), entries, limit);

	std::vector<trade_entry_t> result;
	for(const auto& entry : entries) {
		result.push_back(make_trade_entry(entry.first.first, entry.second));
	}
	return result;
}

std::vector<trade_entry_t> Node::get_trade_history_for(
			const vnx::optional<addr_t>& bid, const vnx::optional<addr_t>& ask, const int32_t& limit, const uint32_t& since) const
{
	if(!bid && !ask) {
		return get_trade_history(limit, since);
	}
	hash_t key;
	if(bid && ask) {
		key = hash_t((*ask) + (*bid));
	} else if(bid) {
		key = hash_t("ANY" + (*bid));
	} else if(ask) {
		key = hash_t((*ask) + "ANY");
	}
	std::vector<std::pair<std::tuple<hash_t, uint32_t, uint32_t>, bool>> entries;
	trade_index.find_last_range(std::make_tuple(key, since, 0), std::make_tuple(key, -1, -1), entries, limit);

	std::vector<trade_entry_t> result;
	for(const auto& entry : entries) {
		const auto& height = std::get<1>(entry.first);
		const auto& counter = std::get<2>(entry.first);
		trade_log_t log;
		if(trade_log.find(std::make_pair(height, counter), log)) {
			result.push_back(make_trade_entry(height, log));
		}
	}
	return result;
}

std::vector<swap_info_t> Node::get_swaps(
		const uint32_t& since, const vnx::optional<addr_t>& token, const vnx::optional<addr_t>& currency, const int32_t& limit) const
{
	std::vector<addr_t> list;
	if(!token && !currency) {
		contract_log.find_range(std::make_tuple(params->swap_binary, since, 0), std::make_tuple(params->swap_binary, -1, -1), list, limit);
	} else {
		hash_t key;
		if(token && currency) {
			key = hash_t(*token + *currency);
		} else if(token) {
			key = hash_t(*token + "ANY");
		} else if(currency) {
			key = hash_t("ANY" + *currency);
		}
		swap_index.find_range(std::make_tuple(key, since, 0), std::make_tuple(key, -1, -1), list, limit);
	}

	std::vector<swap_info_t> result;
	for(const auto& address : list) {
		result.push_back(get_swap_info(address));
	}
	if(token) {
		std::sort(result.begin(), result.end(), [](const swap_info_t& L, const swap_info_t& R) -> bool {
			return L.balance[0] > R.balance[0];
		});
	} else if(currency) {
		std::sort(result.begin(), result.end(), [](const swap_info_t& L, const swap_info_t& R) -> bool {
			return L.balance[1] > R.balance[1];
		});
	} else {
		std::sort(result.begin(), result.end(), [](const swap_info_t& L, const swap_info_t& R) -> bool {
			if(!L.user_total[0] || !L.user_total[1]) {
				return false;
			}
			if(!R.user_total[0] || !R.user_total[1]) {
				return true;
			}
			return (L.avg_apy_7d[0] + L.avg_apy_7d[1]) > (R.avg_apy_7d[0] + R.avg_apy_7d[1]);
		});
	}
	return result;
}

swap_info_t Node::get_swap_info(const addr_t& address) const
{
	auto swap = get_contract_as<const contract::Executable>(address);
	if(!swap) {
		throw std::runtime_error("no such swap: " + address.to_string());
	}
	const auto height = get_height();

	swap_info_t out;
	out.name = swap->name;
	out.address = address;

	auto data = read_storage(address);
	const auto ref_volume = to_ref(data["volume"]);
	const auto tokens = read_storage_array(address, to_ref(data["tokens"]));
	const auto volume = read_storage_array(address, ref_volume);
	for(size_t i = 0; i < 2 && i < tokens.size(); ++i) {
		out.tokens[i] = to_addr(tokens[i]);
		out.volume[i] = to_uint(volume[i]);
		out.wallet[i] = get_balance(address, out.tokens[i]);
	}

	const auto fee_rates = read_storage_array(address, to_ref(data["fee_rates"]));
	for(const auto& value : fee_rates) {
		out.fee_rates.push_back(uint128(to_uint(value)).to_double() / pow(2, 64));
	}
	const auto state = read_storage_array(address, to_ref(data["state"]));

	uint256_t prev_fees_paid_1d[2] = {};
	uint256_t prev_fees_paid_7d[2] = {};

	for(const auto& entry : state) {
		auto obj = read_storage_object(address, to_ref(entry));
		const auto balance = read_storage_array(address, to_ref(obj["balance"]));
		const auto fees_paid = read_storage_array(address, to_ref(obj["fees_paid"]));
		const auto fees_claimed = read_storage_array(address, to_ref(obj["fees_claimed"]));
		const auto user_total = read_storage_array(address, to_ref(obj["user_total"]));

		swap_pool_info_t pool;
		for(size_t i = 0; i < 2 && i < balance.size(); ++i) {
			pool.balance[i] = to_uint(balance[i]);
		}
		for(size_t i = 0; i < 2 && i < fees_paid.size(); ++i) {
			pool.fees_paid[i] = to_uint(fees_paid[i]);
		}
		for(size_t i = 0; i < 2 && i < fees_claimed.size(); ++i) {
			pool.fees_claimed[i] = to_uint(fees_claimed[i]);
		}
		for(size_t i = 0; i < 2 && i < user_total.size(); ++i) {
			pool.user_total[i] = to_uint(user_total[i]);
		}
		for(size_t i = 0; i < 2; ++i) {
			out.balance[i] += pool.balance[i];
			out.fees_paid[i] += pool.fees_paid[i];
			out.fees_claimed[i] += pool.fees_claimed[i];
			out.user_total[i] += pool.user_total[i];
		}
		const auto ref_fees_paid = to_ref(obj["fees_paid"]);
		{
			const auto prev_fees_paid = read_storage_array(address, ref_fees_paid, height - std::min(8640u, height));
			for(size_t i = 0; i < 2 && i < prev_fees_paid.size(); ++i) {
				prev_fees_paid_1d[i] += to_uint(prev_fees_paid[i]);
			}
		}
		{
			const auto prev_fees_paid = read_storage_array(address, ref_fees_paid, height - std::min(60480u, height));
			for(size_t i = 0; i < 2 && i < prev_fees_paid.size(); ++i) {
				prev_fees_paid_7d[i] += to_uint(prev_fees_paid[i]);
			}
		}
		out.pools.push_back(pool);
	}

	out.volume_1d = out.volume;
	out.volume_7d = out.volume;
	{
		const auto prev_volume = read_storage_array(address, ref_volume, height - std::min(8640u, height));
		for(size_t i = 0; i < 2 && i < prev_volume.size(); ++i) {
			out.volume_1d[i] = out.volume[i] - to_uint(prev_volume[i]);
		}
	}
	{
		const auto prev_volume = read_storage_array(address, ref_volume, height - std::min(60480u, height));
		for(size_t i = 0; i < 2 && i < prev_volume.size(); ++i) {
			out.volume_7d[i] = out.volume[i] - to_uint(prev_volume[i]);
		}
	}
	for(size_t i = 0; i < 2; ++i) {
		out.avg_apy_1d[i] = uint128(365 * (out.fees_paid[i] - prev_fees_paid_1d[i])).to_double() / out.user_total[i].to_double();
	}
	for(size_t i = 0; i < 2; ++i) {
		out.avg_apy_7d[i] = uint128(52 * (out.fees_paid[i] - prev_fees_paid_7d[i])).to_double() / out.user_total[i].to_double();
	}
	return out;
}

swap_user_info_t Node::get_swap_user_info(const addr_t& address, const addr_t& user) const
{
	swap_user_info_t out;
	const auto key = storage->lookup(address, vm::to_binary(user));
	const auto users = read_storage_field(address, "users");
	const auto user_ref = storage->read(address, to_ref(users.first), key);
	if(!user_ref) {
		return out;
	}
	auto data = read_storage_object(address, to_ref(user_ref.get()));

	out.pool_idx = to_uint(data["pool_idx"]).lower().lower();
	out.unlock_height = to_uint(data["unlock_height"]);
	const auto balance = read_storage_array(address, to_ref(data["balance"]));
	const auto last_user_total = read_storage_array(address, to_ref(data["last_user_total"]));
	const auto last_fees_paid = read_storage_array(address, to_ref(data["last_fees_paid"]));
	for(size_t i = 0; i < 2 && i < balance.size(); ++i) {
		out.balance[i] = to_uint(balance[i]);
	}
	for(size_t i = 0; i < 2 && i < last_user_total.size(); ++i) {
		out.last_user_total[i] = to_uint(last_user_total[i]);
	}
	for(size_t i = 0; i < 2 && i < last_fees_paid.size(); ++i) {
		out.last_fees_paid[i] = to_uint(last_fees_paid[i]);
	}
	out.fees_earned = get_swap_fees_earned(address, user);
	out.equivalent_liquidity = get_swap_equivalent_liquidity(address, user);
	return out;
}

std::vector<swap_entry_t> Node::get_swap_history(const addr_t& address, const int32_t& limit) const
{
	const auto info = get_swap_info(address);
	std::array<std::shared_ptr<const contract::TokenBase>, 2> tokens;
	for(int i = 0; i < 2; ++i) {
		tokens[i] = get_contract_as<const contract::TokenBase>(info.tokens[i]);
	}

	std::vector<swap_entry_t> result;
	for(const auto& entry : get_exec_history(address, limit, true)) {
		swap_entry_t out;
		out.height = entry.height;
		out.time_stamp = entry.time_stamp;
		out.txid = entry.txid;
		out.user = entry.user;
		out.index = -1;
		if(entry.method == "trade") {
			if(entry.deposit && entry.args.size() >= 2) {
				const auto index = entry.args[0].to<uint32_t>();
				out.type = (index ? "BUY" : "SELL");
				out.index = index;
				out.amount = entry.deposit->second;
				out.user = entry.args[1].to<addr_t>();
			}
		} else if(entry.method == "add_liquid" || entry.method == "rem_liquid") {
			out.type = (entry.method == "add_liquid") ? "ADD" : "REMOVE";
			if(entry.args.size() >= 1) {
				out.index = entry.args[0].to<uint32_t>();
				if(entry.deposit) {
					out.amount = entry.deposit->second;
				} else if(entry.args.size() >= 2) {
					out.amount = entry.args[1].to<uint128>();
				}
			}
		} else if(entry.method == "rem_all_liquid") {
			out.type = "REMOVE_ALL";
		} else if(entry.method == "payout") {
			out.type = "PAYOUT";
		} else if(entry.method == "switch_pool") {
			out.type = "SWITCH";
		}
		if(out.index < 2) {
			if(auto token = tokens[out.index]) {
				out.value = to_value(out.amount, token->decimals);
				out.symbol = token->symbol;
			} else if(info.tokens[out.index] == addr_t()) {
				out.value = to_value(out.amount, params->decimals);
				out.symbol = "MMX";
			}
		}
		result.push_back(out);
	}
	return result;
}

std::array<uint128, 2> Node::get_swap_trade_estimate(const addr_t& address, const uint32_t& i, const uint128& amount, const int32_t& num_iter) const
{
	const auto info = get_swap_info(address);

	std::vector<vnx::Variant> args;
	args.emplace_back(i);
	args.emplace_back(address.to_string());
	args.emplace_back(nullptr);
	args.emplace_back(num_iter);
	const auto ret = call_contract(address, "trade", args, nullptr, std::make_pair(info.tokens[i], amount)).to<std::array<uint128, 2>>();
	return {ret[0] - ret[1], ret[1]};
}

std::array<uint128, 2> Node::get_swap_fees_earned(const addr_t& address, const addr_t& user) const
{
	return call_contract(address, "get_earned_fees", {vnx::Variant(user.to_string())}).to<std::array<uint128, 2>>();
}

std::array<uint128, 2> Node::get_swap_equivalent_liquidity(const addr_t& address, const addr_t& user) const
{
	return call_contract(address, "rem_all_liquid", {vnx::Variant(true)}, user).to<std::array<uint128, 2>>();
}

std::map<addr_t, std::array<std::pair<addr_t, uint128>, 2>> Node::get_swap_liquidity_by(const std::vector<addr_t>& addresses) const
{
	std::map<addr_t, std::array<uint128, 2>> swaps;
	for(const auto& address : addresses) {
		std::vector<std::pair<std::pair<addr_t, addr_t>, std::array<uint128, 2>>> entries;
		swap_liquid_map.find_range(std::make_pair(address, addr_t()), std::make_pair(address, addr_t::ones()), entries);
		for(const auto& entry : entries) {
			auto& out = swaps[entry.first.second];
			for(int i = 0; i < 2; ++i) {
				out[i] += entry.second[i];
			}
		}
	}
	std::map<addr_t, std::array<std::pair<addr_t, uint128>, 2>> result;
	for(const auto& entry : swaps) {
		auto& out = result[entry.first];
		const auto info = get_swap_info(entry.first);
		for(int i = 0; i < 2; ++i) {
			out[i] = std::make_pair(info.tokens[i], entry.second[i]);
		}
	}
	return result;
}

std::vector<std::shared_ptr<const BlockHeader>> Node::get_farmed_blocks(
		const std::vector<pubkey_t>& farmer_keys, const vnx::bool_t& full_blocks, const uint32_t& since, const int32_t& limit) const
{
	std::vector<farmed_block_info_t> entries;
	for(const auto& key : farmer_keys) {
		std::vector<farmed_block_info_t> tmp;
		farmer_block_map.find_last_range(std::make_pair(key, since), std::make_pair(key, -1), tmp, size_t(limit));
		entries.insert(entries.end(), tmp.begin(), tmp.end());
	}
	// need to sort in case multiple keys
	std::sort(entries.begin(), entries.end(), [](const farmed_block_info_t& L, const farmed_block_info_t& R) -> bool {
		return L.height > R.height;
	});
	if(limit >= 0) {
		if(entries.size() > size_t(limit)) {
			entries.resize(limit);
		}
	} else {
		std::reverse(entries.begin(), entries.end());
	}
	std::vector<std::shared_ptr<const BlockHeader>> out;
	for(const auto& entry : entries) {
		out.push_back(get_block_at_ex(entry.height, full_blocks));
	}
	return out;
}

farmed_block_summary_t Node::get_farmed_block_summary(const std::vector<pubkey_t>& farmer_keys, const uint32_t& since) const
{
	farmed_block_summary_t out;
	for(const auto& key : farmer_keys) {
		std::vector<farmed_block_info_t> tmp;
		farmer_block_map.find_range(std::make_pair(key, since), std::make_pair(key, -1), tmp);
		for(const auto& entry : tmp) {
			out.num_blocks++;
			out.last_height = std::max(entry.height, out.last_height);
			out.total_rewards += entry.reward;
			out.reward_map[entry.reward_addr] += entry.reward;
		}
	}
	return out;
}

std::vector<std::pair<pubkey_t, uint32_t>> Node::get_farmer_ranking(const int32_t& limit) const
{
	if(limit < 0) {
		return farmer_ranking;
	}
	std::vector<std::pair<pubkey_t, uint32_t>> out;
	for(const auto& entry : farmer_ranking) {
		if(out.size() < size_t(limit)) {
			out.push_back(entry);
		} else {
			break;
		}
	}
	return out;
}

std::tuple<pooling_error_e, std::string> Node::verify_plot_nft_target(const addr_t& address, const addr_t& pool_target) const
{
	if(!is_synced) {
		throw std::logic_error("out of sync");
	}
	try {
		const auto exec = get_contract_as<contract::Executable>(address);
		if(!exec || exec->binary != params->plot_nft_binary) {
			return {pooling_error_e::INVALID_CONTRACT, "Not a Plot NFT contract: " + address.to_string()};
		}
		const auto target = get_plot_nft_target(address);
		if(target != pool_target) {
			return {pooling_error_e::INVALID_CONTRACT, "Plot NFT not pointing at expected pool target: " + target.to_string()};
		}
	} catch(const std::exception& ex) {
		return {pooling_error_e::INVALID_CONTRACT, "Plot NFT target resolution failed with: " + std::string(ex.what())};
	}
	return {pooling_error_e::NONE, ""};
}

std::tuple<pooling_error_e, std::string> Node::verify_partial(
		std::shared_ptr<const Partial> partial, const vnx::optional<addr_t>& pool_target) const
{
	if(!is_synced) {
		throw std::logic_error("out of sync");
	}
	if(!partial) {
		throw std::logic_error("partial == null");
	}
	if(!partial->proof) {
		return {pooling_error_e::INVALID_PROOF, "Partial has no proof"};
	}
	if(partial->hash != partial->calc_hash()) {
		return {pooling_error_e::INVALID_SIGNATURE, "Message hash mismatch"};
	}
	if(!partial->farmer_sig) {
		return {pooling_error_e::INVALID_SIGNATURE, "Missing signature"};
	}
	if(!partial->farmer_sig->verify(partial->proof->farmer_key, partial->hash)) {
		return {pooling_error_e::INVALID_SIGNATURE, "Signature verification failed"};
	}
	if(partial->vdf_height > get_vdf_height()) {
		return {pooling_error_e::CHALLENGE_NOT_CONFIRMED, "Partial height not reached yet"};
	}

	hash_t challenge;
	uint64_t space_diff = 0;
	if(!find_challenge(partial->vdf_height, challenge, space_diff)) {
		return {pooling_error_e::CHALLENGE_NOT_FOUND, "Could not find challenge"};
	}
	if(partial->proof->challenge != challenge) {
		return {pooling_error_e::CHALLENGE_REVERTED, "Challenge mismatch, expected " + challenge.to_string()};
	}

	try {
		verify_proof(partial->proof, challenge, partial->proof->difficulty, partial->vdf_height);
	} catch(const std::exception& ex) {
		return {pooling_error_e::INVALID_PROOF, "Invalid proof: " + std::string(ex.what())};
	}

	if(pool_target) {
		if(auto nft = std::dynamic_pointer_cast<const ProofOfSpaceNFT>(partial->proof))
		{
			if(partial->contract != nft->contract) {
				return {pooling_error_e::INVALID_CONTRACT, "Partial 'contract' does not match proof of space"};
			}
			const auto ret = verify_plot_nft_target(nft->contract, *pool_target);
			if(std::get<0>(ret) != pooling_error_e::NONE) {
				return ret;
			}
		} else {
			return {pooling_error_e::INVALID_CONTRACT, "Invalid proof type: " + partial->proof->get_type_name()};
		}
	}
	return {pooling_error_e::NONE, ""};
}

uint32_t Node::get_vdf_height() const
{
	return get_vdf_peak_ex().first;
}

hash_t Node::get_vdf_peak() const
{
	return get_vdf_peak_ex().second;
}

void Node::http_request_async(	std::shared_ptr<const vnx::addons::HttpRequest> request, const std::string& sub_path,
								const vnx::request_id_t& request_id) const
{
	http->http_request(request, sub_path, request_id, vnx_request->session);
}

void Node::http_request_chunk_async(std::shared_ptr<const vnx::addons::HttpRequest> request, const std::string& sub_path,
									const int64_t& offset, const int64_t& max_bytes, const vnx::request_id_t& request_id) const
{
	throw std::logic_error("not implemented");
}

void Node::async_api_call(std::shared_ptr<const vnx::Value> method, const vnx::request_id_t& request_id)
{
	try {
		std::shared_ptr<vnx::Value> ret;
		{
			std::shared_lock lock(db_mutex);
			ret = NodeBase::vnx_call_switch(method, request_id);
		}
		vnx_async_return(request_id, ret);
	}
	catch(const std::exception& ex) {
		vnx_async_return_ex(request_id, ex);
	}
	catch(...) {
		vnx_async_return(request_id, vnx::InternalError::create());
	}
}

std::shared_ptr<vnx::Value> Node::vnx_call_switch(std::shared_ptr<const vnx::Value> method, const vnx::request_id_t& request_id)
{
	switch(method->get_type_hash())
	{
		// Note: NOT thread-safe:
		// - http_request()
		// - get_network_info()
		case Node_get_block::VNX_TYPE_ID:
		case Node_get_block_at::VNX_TYPE_ID:
		case Node_get_header::VNX_TYPE_ID:
		case Node_get_header_at::VNX_TYPE_ID:
		case Node_get_tx_ids::VNX_TYPE_ID:
		case Node_get_tx_ids_at::VNX_TYPE_ID:
		case Node_get_tx_ids_since::VNX_TYPE_ID:
		case Node_get_tx_height::VNX_TYPE_ID:
		case Node_get_tx_info::VNX_TYPE_ID:
		case Node_get_tx_info_for::VNX_TYPE_ID:
		case Node_get_transaction::VNX_TYPE_ID:
		case Node_get_transactions::VNX_TYPE_ID:
		case Node_get_history::VNX_TYPE_ID:
		case Node_get_history_memo::VNX_TYPE_ID:
		case Node_get_contract::VNX_TYPE_ID:
		case Node_get_contract_for::VNX_TYPE_ID:
		case Node_get_contracts::VNX_TYPE_ID:
		case Node_get_contracts_by::VNX_TYPE_ID:
		case Node_get_contracts_owned_by::VNX_TYPE_ID:
		case Node_get_balance::VNX_TYPE_ID:
		case Node_get_total_balance::VNX_TYPE_ID:
		case Node_get_balances::VNX_TYPE_ID:
		case Node_get_contract_balances::VNX_TYPE_ID:
		case Node_get_total_balances::VNX_TYPE_ID:
		case Node_get_all_balances::VNX_TYPE_ID:
		case Node_get_exec_history::VNX_TYPE_ID:
		case Node_read_storage::VNX_TYPE_ID:
		case Node_dump_storage::VNX_TYPE_ID:
		case Node_read_storage_var::VNX_TYPE_ID:
		case Node_read_storage_entry_var::VNX_TYPE_ID:
		case Node_read_storage_field::VNX_TYPE_ID:
		case Node_read_storage_entry_addr::VNX_TYPE_ID:
		case Node_read_storage_entry_string::VNX_TYPE_ID:
		case Node_read_storage_array::VNX_TYPE_ID:
		case Node_read_storage_map::VNX_TYPE_ID:
		case Node_read_storage_object::VNX_TYPE_ID:
		case Node_call_contract::VNX_TYPE_ID:
		case Node_get_total_supply::VNX_TYPE_ID:
		case Node_get_offer::VNX_TYPE_ID:
		case Node_fetch_offers::VNX_TYPE_ID:
		case Node_get_offers::VNX_TYPE_ID:
		case Node_get_offers_by::VNX_TYPE_ID:
		case Node_get_recent_offers::VNX_TYPE_ID:
		case Node_get_recent_offers_for::VNX_TYPE_ID:
		case Node_get_trade_history::VNX_TYPE_ID:
		case Node_get_trade_history_for::VNX_TYPE_ID:
		case Node_get_swaps::VNX_TYPE_ID:
		case Node_get_swap_info::VNX_TYPE_ID:
		case Node_get_swap_user_info::VNX_TYPE_ID:
		case Node_get_swap_history::VNX_TYPE_ID:
		case Node_get_swap_trade_estimate::VNX_TYPE_ID:
		case Node_get_swap_fees_earned::VNX_TYPE_ID:
		case Node_get_swap_equivalent_liquidity::VNX_TYPE_ID:
		case Node_get_swap_liquidity_by::VNX_TYPE_ID:
		case Node_get_farmed_blocks::VNX_TYPE_ID:
		case Node_get_farmer_ranking::VNX_TYPE_ID:
		case Node_get_farmed_block_summary::VNX_TYPE_ID:
		case Node_get_plot_nft_info::VNX_TYPE_ID:
		case Node_get_plot_nft_target::VNX_TYPE_ID:
		case Node_validate::VNX_TYPE_ID:
		case Node_verify_plot_nft_target::VNX_TYPE_ID:
		case Node_verify_partial::VNX_TYPE_ID:
		case Node_get_vdf_peak::VNX_TYPE_ID:
		case Node_get_vdf_height::VNX_TYPE_ID:
			api_threads->add_task(std::bind(&Node::async_api_call, this, method, request_id));
			return nullptr;
		default:
			return NodeBase::vnx_call_switch(method, request_id);
	}
}


} // mmx
