
// AUTO GENERATED by vnxcppcodegen

#include <mmx/package.hxx>
#include <mmx/BlockHeader.hxx>
#include <mmx/ChainParams.hxx>
#include <mmx/ProofOfSpace.hxx>
#include <mmx/addr_t.hpp>
#include <mmx/block_index_t.hxx>
#include <mmx/hash_t.hpp>
#include <mmx/signature_t.hpp>
#include <mmx/uint128.hpp>
#include <vnx/Value.h>

#include <vnx/vnx.h>


namespace mmx {


const vnx::Hash64 BlockHeader::VNX_TYPE_HASH(0xcaae941a2fc712a6ull);
const vnx::Hash64 BlockHeader::VNX_CODE_HASH(0xcbfd61de36e5fdabull);

vnx::Hash64 BlockHeader::get_type_hash() const {
	return VNX_TYPE_HASH;
}

std::string BlockHeader::get_type_name() const {
	return "mmx.BlockHeader";
}

const vnx::TypeCode* BlockHeader::get_type_code() const {
	return mmx::vnx_native_type_code_BlockHeader;
}

std::shared_ptr<BlockHeader> BlockHeader::create() {
	return std::make_shared<BlockHeader>();
}

std::shared_ptr<vnx::Value> BlockHeader::clone() const {
	return std::make_shared<BlockHeader>(*this);
}

void BlockHeader::read(vnx::TypeInput& _in, const vnx::TypeCode* _type_code, const uint16_t* _code) {
	vnx::read(_in, *this, _type_code, _code);
}

void BlockHeader::write(vnx::TypeOutput& _out, const vnx::TypeCode* _type_code, const uint16_t* _code) const {
	vnx::write(_out, *this, _type_code, _code);
}

void BlockHeader::accept(vnx::Visitor& _visitor) const {
	const vnx::TypeCode* _type_code = mmx::vnx_native_type_code_BlockHeader;
	_visitor.type_begin(*_type_code);
	_visitor.type_field(_type_code->fields[0], 0); vnx::accept(_visitor, version);
	_visitor.type_field(_type_code->fields[1], 1); vnx::accept(_visitor, support_flags);
	_visitor.type_field(_type_code->fields[2], 2); vnx::accept(_visitor, hash);
	_visitor.type_field(_type_code->fields[3], 3); vnx::accept(_visitor, prev);
	_visitor.type_field(_type_code->fields[4], 4); vnx::accept(_visitor, height);
	_visitor.type_field(_type_code->fields[5], 5); vnx::accept(_visitor, vdf_height);
	_visitor.type_field(_type_code->fields[6], 6); vnx::accept(_visitor, nonce);
	_visitor.type_field(_type_code->fields[7], 7); vnx::accept(_visitor, time_stamp);
	_visitor.type_field(_type_code->fields[8], 8); vnx::accept(_visitor, time_diff);
	_visitor.type_field(_type_code->fields[9], 9); vnx::accept(_visitor, space_diff);
	_visitor.type_field(_type_code->fields[10], 10); vnx::accept(_visitor, weight);
	_visitor.type_field(_type_code->fields[11], 11); vnx::accept(_visitor, total_weight);
	_visitor.type_field(_type_code->fields[12], 12); vnx::accept(_visitor, vdf_count);
	_visitor.type_field(_type_code->fields[13], 13); vnx::accept(_visitor, vdf_iters);
	_visitor.type_field(_type_code->fields[14], 14); vnx::accept(_visitor, vdf_output);
	_visitor.type_field(_type_code->fields[15], 15); vnx::accept(_visitor, vdf_reward_addr);
	_visitor.type_field(_type_code->fields[16], 16); vnx::accept(_visitor, vdf_reward_payout);
	_visitor.type_field(_type_code->fields[17], 17); vnx::accept(_visitor, proof);
	_visitor.type_field(_type_code->fields[18], 18); vnx::accept(_visitor, proof_hash);
	_visitor.type_field(_type_code->fields[19], 19); vnx::accept(_visitor, challenge);
	_visitor.type_field(_type_code->fields[20], 20); vnx::accept(_visitor, is_space_fork);
	_visitor.type_field(_type_code->fields[21], 21); vnx::accept(_visitor, space_fork_len);
	_visitor.type_field(_type_code->fields[22], 22); vnx::accept(_visitor, space_fork_proofs);
	_visitor.type_field(_type_code->fields[23], 23); vnx::accept(_visitor, reward_amount);
	_visitor.type_field(_type_code->fields[24], 24); vnx::accept(_visitor, reward_addr);
	_visitor.type_field(_type_code->fields[25], 25); vnx::accept(_visitor, reward_contract);
	_visitor.type_field(_type_code->fields[26], 26); vnx::accept(_visitor, reward_account);
	_visitor.type_field(_type_code->fields[27], 27); vnx::accept(_visitor, reward_vote);
	_visitor.type_field(_type_code->fields[28], 28); vnx::accept(_visitor, reward_vote_sum);
	_visitor.type_field(_type_code->fields[29], 29); vnx::accept(_visitor, reward_vote_count);
	_visitor.type_field(_type_code->fields[30], 30); vnx::accept(_visitor, base_reward);
	_visitor.type_field(_type_code->fields[31], 31); vnx::accept(_visitor, static_cost);
	_visitor.type_field(_type_code->fields[32], 32); vnx::accept(_visitor, total_cost);
	_visitor.type_field(_type_code->fields[33], 33); vnx::accept(_visitor, tx_count);
	_visitor.type_field(_type_code->fields[34], 34); vnx::accept(_visitor, tx_fees);
	_visitor.type_field(_type_code->fields[35], 35); vnx::accept(_visitor, txfee_buffer);
	_visitor.type_field(_type_code->fields[36], 36); vnx::accept(_visitor, tx_hash);
	_visitor.type_field(_type_code->fields[37], 37); vnx::accept(_visitor, farmer_sig);
	_visitor.type_field(_type_code->fields[38], 38); vnx::accept(_visitor, content_hash);
	_visitor.type_end(*_type_code);
}

void BlockHeader::write(std::ostream& _out) const {
	_out << "{\"__type\": \"mmx.BlockHeader\"";
	_out << ", \"version\": "; vnx::write(_out, version);
	_out << ", \"support_flags\": "; vnx::write(_out, support_flags);
	_out << ", \"hash\": "; vnx::write(_out, hash);
	_out << ", \"prev\": "; vnx::write(_out, prev);
	_out << ", \"height\": "; vnx::write(_out, height);
	_out << ", \"vdf_height\": "; vnx::write(_out, vdf_height);
	_out << ", \"nonce\": "; vnx::write(_out, nonce);
	_out << ", \"time_stamp\": "; vnx::write(_out, time_stamp);
	_out << ", \"time_diff\": "; vnx::write(_out, time_diff);
	_out << ", \"space_diff\": "; vnx::write(_out, space_diff);
	_out << ", \"weight\": "; vnx::write(_out, weight);
	_out << ", \"total_weight\": "; vnx::write(_out, total_weight);
	_out << ", \"vdf_count\": "; vnx::write(_out, vdf_count);
	_out << ", \"vdf_iters\": "; vnx::write(_out, vdf_iters);
	_out << ", \"vdf_output\": "; vnx::write(_out, vdf_output);
	_out << ", \"vdf_reward_addr\": "; vnx::write(_out, vdf_reward_addr);
	_out << ", \"vdf_reward_payout\": "; vnx::write(_out, vdf_reward_payout);
	_out << ", \"proof\": "; vnx::write(_out, proof);
	_out << ", \"proof_hash\": "; vnx::write(_out, proof_hash);
	_out << ", \"challenge\": "; vnx::write(_out, challenge);
	_out << ", \"is_space_fork\": "; vnx::write(_out, is_space_fork);
	_out << ", \"space_fork_len\": "; vnx::write(_out, space_fork_len);
	_out << ", \"space_fork_proofs\": "; vnx::write(_out, space_fork_proofs);
	_out << ", \"reward_amount\": "; vnx::write(_out, reward_amount);
	_out << ", \"reward_addr\": "; vnx::write(_out, reward_addr);
	_out << ", \"reward_contract\": "; vnx::write(_out, reward_contract);
	_out << ", \"reward_account\": "; vnx::write(_out, reward_account);
	_out << ", \"reward_vote\": "; vnx::write(_out, reward_vote);
	_out << ", \"reward_vote_sum\": "; vnx::write(_out, reward_vote_sum);
	_out << ", \"reward_vote_count\": "; vnx::write(_out, reward_vote_count);
	_out << ", \"base_reward\": "; vnx::write(_out, base_reward);
	_out << ", \"static_cost\": "; vnx::write(_out, static_cost);
	_out << ", \"total_cost\": "; vnx::write(_out, total_cost);
	_out << ", \"tx_count\": "; vnx::write(_out, tx_count);
	_out << ", \"tx_fees\": "; vnx::write(_out, tx_fees);
	_out << ", \"txfee_buffer\": "; vnx::write(_out, txfee_buffer);
	_out << ", \"tx_hash\": "; vnx::write(_out, tx_hash);
	_out << ", \"farmer_sig\": "; vnx::write(_out, farmer_sig);
	_out << ", \"content_hash\": "; vnx::write(_out, content_hash);
	_out << "}";
}

void BlockHeader::read(std::istream& _in) {
	if(auto _json = vnx::read_json(_in)) {
		from_object(_json->to_object());
	}
}

vnx::Object BlockHeader::to_object() const {
	vnx::Object _object;
	_object["__type"] = "mmx.BlockHeader";
	_object["version"] = version;
	_object["support_flags"] = support_flags;
	_object["hash"] = hash;
	_object["prev"] = prev;
	_object["height"] = height;
	_object["vdf_height"] = vdf_height;
	_object["nonce"] = nonce;
	_object["time_stamp"] = time_stamp;
	_object["time_diff"] = time_diff;
	_object["space_diff"] = space_diff;
	_object["weight"] = weight;
	_object["total_weight"] = total_weight;
	_object["vdf_count"] = vdf_count;
	_object["vdf_iters"] = vdf_iters;
	_object["vdf_output"] = vdf_output;
	_object["vdf_reward_addr"] = vdf_reward_addr;
	_object["vdf_reward_payout"] = vdf_reward_payout;
	_object["proof"] = proof;
	_object["proof_hash"] = proof_hash;
	_object["challenge"] = challenge;
	_object["is_space_fork"] = is_space_fork;
	_object["space_fork_len"] = space_fork_len;
	_object["space_fork_proofs"] = space_fork_proofs;
	_object["reward_amount"] = reward_amount;
	_object["reward_addr"] = reward_addr;
	_object["reward_contract"] = reward_contract;
	_object["reward_account"] = reward_account;
	_object["reward_vote"] = reward_vote;
	_object["reward_vote_sum"] = reward_vote_sum;
	_object["reward_vote_count"] = reward_vote_count;
	_object["base_reward"] = base_reward;
	_object["static_cost"] = static_cost;
	_object["total_cost"] = total_cost;
	_object["tx_count"] = tx_count;
	_object["tx_fees"] = tx_fees;
	_object["txfee_buffer"] = txfee_buffer;
	_object["tx_hash"] = tx_hash;
	_object["farmer_sig"] = farmer_sig;
	_object["content_hash"] = content_hash;
	return _object;
}

void BlockHeader::from_object(const vnx::Object& _object) {
	for(const auto& _entry : _object.field) {
		if(_entry.first == "base_reward") {
			_entry.second.to(base_reward);
		} else if(_entry.first == "challenge") {
			_entry.second.to(challenge);
		} else if(_entry.first == "content_hash") {
			_entry.second.to(content_hash);
		} else if(_entry.first == "farmer_sig") {
			_entry.second.to(farmer_sig);
		} else if(_entry.first == "hash") {
			_entry.second.to(hash);
		} else if(_entry.first == "height") {
			_entry.second.to(height);
		} else if(_entry.first == "is_space_fork") {
			_entry.second.to(is_space_fork);
		} else if(_entry.first == "nonce") {
			_entry.second.to(nonce);
		} else if(_entry.first == "prev") {
			_entry.second.to(prev);
		} else if(_entry.first == "proof") {
			_entry.second.to(proof);
		} else if(_entry.first == "proof_hash") {
			_entry.second.to(proof_hash);
		} else if(_entry.first == "reward_account") {
			_entry.second.to(reward_account);
		} else if(_entry.first == "reward_addr") {
			_entry.second.to(reward_addr);
		} else if(_entry.first == "reward_amount") {
			_entry.second.to(reward_amount);
		} else if(_entry.first == "reward_contract") {
			_entry.second.to(reward_contract);
		} else if(_entry.first == "reward_vote") {
			_entry.second.to(reward_vote);
		} else if(_entry.first == "reward_vote_count") {
			_entry.second.to(reward_vote_count);
		} else if(_entry.first == "reward_vote_sum") {
			_entry.second.to(reward_vote_sum);
		} else if(_entry.first == "space_diff") {
			_entry.second.to(space_diff);
		} else if(_entry.first == "space_fork_len") {
			_entry.second.to(space_fork_len);
		} else if(_entry.first == "space_fork_proofs") {
			_entry.second.to(space_fork_proofs);
		} else if(_entry.first == "static_cost") {
			_entry.second.to(static_cost);
		} else if(_entry.first == "support_flags") {
			_entry.second.to(support_flags);
		} else if(_entry.first == "time_diff") {
			_entry.second.to(time_diff);
		} else if(_entry.first == "time_stamp") {
			_entry.second.to(time_stamp);
		} else if(_entry.first == "total_cost") {
			_entry.second.to(total_cost);
		} else if(_entry.first == "total_weight") {
			_entry.second.to(total_weight);
		} else if(_entry.first == "tx_count") {
			_entry.second.to(tx_count);
		} else if(_entry.first == "tx_fees") {
			_entry.second.to(tx_fees);
		} else if(_entry.first == "tx_hash") {
			_entry.second.to(tx_hash);
		} else if(_entry.first == "txfee_buffer") {
			_entry.second.to(txfee_buffer);
		} else if(_entry.first == "vdf_count") {
			_entry.second.to(vdf_count);
		} else if(_entry.first == "vdf_height") {
			_entry.second.to(vdf_height);
		} else if(_entry.first == "vdf_iters") {
			_entry.second.to(vdf_iters);
		} else if(_entry.first == "vdf_output") {
			_entry.second.to(vdf_output);
		} else if(_entry.first == "vdf_reward_addr") {
			_entry.second.to(vdf_reward_addr);
		} else if(_entry.first == "vdf_reward_payout") {
			_entry.second.to(vdf_reward_payout);
		} else if(_entry.first == "version") {
			_entry.second.to(version);
		} else if(_entry.first == "weight") {
			_entry.second.to(weight);
		}
	}
}

vnx::Variant BlockHeader::get_field(const std::string& _name) const {
	if(_name == "version") {
		return vnx::Variant(version);
	}
	if(_name == "support_flags") {
		return vnx::Variant(support_flags);
	}
	if(_name == "hash") {
		return vnx::Variant(hash);
	}
	if(_name == "prev") {
		return vnx::Variant(prev);
	}
	if(_name == "height") {
		return vnx::Variant(height);
	}
	if(_name == "vdf_height") {
		return vnx::Variant(vdf_height);
	}
	if(_name == "nonce") {
		return vnx::Variant(nonce);
	}
	if(_name == "time_stamp") {
		return vnx::Variant(time_stamp);
	}
	if(_name == "time_diff") {
		return vnx::Variant(time_diff);
	}
	if(_name == "space_diff") {
		return vnx::Variant(space_diff);
	}
	if(_name == "weight") {
		return vnx::Variant(weight);
	}
	if(_name == "total_weight") {
		return vnx::Variant(total_weight);
	}
	if(_name == "vdf_count") {
		return vnx::Variant(vdf_count);
	}
	if(_name == "vdf_iters") {
		return vnx::Variant(vdf_iters);
	}
	if(_name == "vdf_output") {
		return vnx::Variant(vdf_output);
	}
	if(_name == "vdf_reward_addr") {
		return vnx::Variant(vdf_reward_addr);
	}
	if(_name == "vdf_reward_payout") {
		return vnx::Variant(vdf_reward_payout);
	}
	if(_name == "proof") {
		return vnx::Variant(proof);
	}
	if(_name == "proof_hash") {
		return vnx::Variant(proof_hash);
	}
	if(_name == "challenge") {
		return vnx::Variant(challenge);
	}
	if(_name == "is_space_fork") {
		return vnx::Variant(is_space_fork);
	}
	if(_name == "space_fork_len") {
		return vnx::Variant(space_fork_len);
	}
	if(_name == "space_fork_proofs") {
		return vnx::Variant(space_fork_proofs);
	}
	if(_name == "reward_amount") {
		return vnx::Variant(reward_amount);
	}
	if(_name == "reward_addr") {
		return vnx::Variant(reward_addr);
	}
	if(_name == "reward_contract") {
		return vnx::Variant(reward_contract);
	}
	if(_name == "reward_account") {
		return vnx::Variant(reward_account);
	}
	if(_name == "reward_vote") {
		return vnx::Variant(reward_vote);
	}
	if(_name == "reward_vote_sum") {
		return vnx::Variant(reward_vote_sum);
	}
	if(_name == "reward_vote_count") {
		return vnx::Variant(reward_vote_count);
	}
	if(_name == "base_reward") {
		return vnx::Variant(base_reward);
	}
	if(_name == "static_cost") {
		return vnx::Variant(static_cost);
	}
	if(_name == "total_cost") {
		return vnx::Variant(total_cost);
	}
	if(_name == "tx_count") {
		return vnx::Variant(tx_count);
	}
	if(_name == "tx_fees") {
		return vnx::Variant(tx_fees);
	}
	if(_name == "txfee_buffer") {
		return vnx::Variant(txfee_buffer);
	}
	if(_name == "tx_hash") {
		return vnx::Variant(tx_hash);
	}
	if(_name == "farmer_sig") {
		return vnx::Variant(farmer_sig);
	}
	if(_name == "content_hash") {
		return vnx::Variant(content_hash);
	}
	return vnx::Variant();
}

void BlockHeader::set_field(const std::string& _name, const vnx::Variant& _value) {
	if(_name == "version") {
		_value.to(version);
	} else if(_name == "support_flags") {
		_value.to(support_flags);
	} else if(_name == "hash") {
		_value.to(hash);
	} else if(_name == "prev") {
		_value.to(prev);
	} else if(_name == "height") {
		_value.to(height);
	} else if(_name == "vdf_height") {
		_value.to(vdf_height);
	} else if(_name == "nonce") {
		_value.to(nonce);
	} else if(_name == "time_stamp") {
		_value.to(time_stamp);
	} else if(_name == "time_diff") {
		_value.to(time_diff);
	} else if(_name == "space_diff") {
		_value.to(space_diff);
	} else if(_name == "weight") {
		_value.to(weight);
	} else if(_name == "total_weight") {
		_value.to(total_weight);
	} else if(_name == "vdf_count") {
		_value.to(vdf_count);
	} else if(_name == "vdf_iters") {
		_value.to(vdf_iters);
	} else if(_name == "vdf_output") {
		_value.to(vdf_output);
	} else if(_name == "vdf_reward_addr") {
		_value.to(vdf_reward_addr);
	} else if(_name == "vdf_reward_payout") {
		_value.to(vdf_reward_payout);
	} else if(_name == "proof") {
		_value.to(proof);
	} else if(_name == "proof_hash") {
		_value.to(proof_hash);
	} else if(_name == "challenge") {
		_value.to(challenge);
	} else if(_name == "is_space_fork") {
		_value.to(is_space_fork);
	} else if(_name == "space_fork_len") {
		_value.to(space_fork_len);
	} else if(_name == "space_fork_proofs") {
		_value.to(space_fork_proofs);
	} else if(_name == "reward_amount") {
		_value.to(reward_amount);
	} else if(_name == "reward_addr") {
		_value.to(reward_addr);
	} else if(_name == "reward_contract") {
		_value.to(reward_contract);
	} else if(_name == "reward_account") {
		_value.to(reward_account);
	} else if(_name == "reward_vote") {
		_value.to(reward_vote);
	} else if(_name == "reward_vote_sum") {
		_value.to(reward_vote_sum);
	} else if(_name == "reward_vote_count") {
		_value.to(reward_vote_count);
	} else if(_name == "base_reward") {
		_value.to(base_reward);
	} else if(_name == "static_cost") {
		_value.to(static_cost);
	} else if(_name == "total_cost") {
		_value.to(total_cost);
	} else if(_name == "tx_count") {
		_value.to(tx_count);
	} else if(_name == "tx_fees") {
		_value.to(tx_fees);
	} else if(_name == "txfee_buffer") {
		_value.to(txfee_buffer);
	} else if(_name == "tx_hash") {
		_value.to(tx_hash);
	} else if(_name == "farmer_sig") {
		_value.to(farmer_sig);
	} else if(_name == "content_hash") {
		_value.to(content_hash);
	}
}

/// \private
std::ostream& operator<<(std::ostream& _out, const BlockHeader& _value) {
	_value.write(_out);
	return _out;
}

/// \private
std::istream& operator>>(std::istream& _in, BlockHeader& _value) {
	_value.read(_in);
	return _in;
}

const vnx::TypeCode* BlockHeader::static_get_type_code() {
	const vnx::TypeCode* type_code = vnx::get_type_code(VNX_TYPE_HASH);
	if(!type_code) {
		type_code = vnx::register_type_code(static_create_type_code());
	}
	return type_code;
}

std::shared_ptr<vnx::TypeCode> BlockHeader::static_create_type_code() {
	auto type_code = std::make_shared<vnx::TypeCode>();
	type_code->name = "mmx.BlockHeader";
	type_code->type_hash = vnx::Hash64(0xcaae941a2fc712a6ull);
	type_code->code_hash = vnx::Hash64(0xcbfd61de36e5fdabull);
	type_code->is_native = true;
	type_code->is_class = true;
	type_code->native_size = sizeof(::mmx::BlockHeader);
	type_code->create_value = []() -> std::shared_ptr<vnx::Value> { return std::make_shared<BlockHeader>(); };
	type_code->fields.resize(39);
	{
		auto& field = type_code->fields[0];
		field.data_size = 4;
		field.name = "version";
		field.code = {3};
	}
	{
		auto& field = type_code->fields[1];
		field.data_size = 4;
		field.name = "support_flags";
		field.code = {3};
	}
	{
		auto& field = type_code->fields[2];
		field.is_extended = true;
		field.name = "hash";
		field.code = {11, 32, 1};
	}
	{
		auto& field = type_code->fields[3];
		field.is_extended = true;
		field.name = "prev";
		field.code = {11, 32, 1};
	}
	{
		auto& field = type_code->fields[4];
		field.data_size = 4;
		field.name = "height";
		field.code = {3};
	}
	{
		auto& field = type_code->fields[5];
		field.data_size = 4;
		field.name = "vdf_height";
		field.code = {3};
	}
	{
		auto& field = type_code->fields[6];
		field.data_size = 8;
		field.name = "nonce";
		field.code = {4};
	}
	{
		auto& field = type_code->fields[7];
		field.data_size = 8;
		field.name = "time_stamp";
		field.code = {8};
	}
	{
		auto& field = type_code->fields[8];
		field.data_size = 8;
		field.name = "time_diff";
		field.code = {4};
	}
	{
		auto& field = type_code->fields[9];
		field.data_size = 8;
		field.name = "space_diff";
		field.code = {4};
	}
	{
		auto& field = type_code->fields[10];
		field.is_extended = true;
		field.name = "weight";
		field.code = {11, 16, 1};
	}
	{
		auto& field = type_code->fields[11];
		field.is_extended = true;
		field.name = "total_weight";
		field.code = {11, 16, 1};
	}
	{
		auto& field = type_code->fields[12];
		field.data_size = 4;
		field.name = "vdf_count";
		field.code = {3};
	}
	{
		auto& field = type_code->fields[13];
		field.data_size = 8;
		field.name = "vdf_iters";
		field.code = {4};
	}
	{
		auto& field = type_code->fields[14];
		field.is_extended = true;
		field.name = "vdf_output";
		field.code = {11, 32, 1};
	}
	{
		auto& field = type_code->fields[15];
		field.is_extended = true;
		field.name = "vdf_reward_addr";
		field.code = {33, 11, 32, 1};
	}
	{
		auto& field = type_code->fields[16];
		field.is_extended = true;
		field.name = "vdf_reward_payout";
		field.code = {33, 11, 32, 1};
	}
	{
		auto& field = type_code->fields[17];
		field.is_extended = true;
		field.name = "proof";
		field.code = {16};
	}
	{
		auto& field = type_code->fields[18];
		field.is_extended = true;
		field.name = "proof_hash";
		field.code = {11, 32, 1};
	}
	{
		auto& field = type_code->fields[19];
		field.is_extended = true;
		field.name = "challenge";
		field.code = {11, 32, 1};
	}
	{
		auto& field = type_code->fields[20];
		field.data_size = 1;
		field.name = "is_space_fork";
		field.code = {31};
	}
	{
		auto& field = type_code->fields[21];
		field.data_size = 4;
		field.name = "space_fork_len";
		field.code = {3};
	}
	{
		auto& field = type_code->fields[22];
		field.data_size = 4;
		field.name = "space_fork_proofs";
		field.code = {3};
	}
	{
		auto& field = type_code->fields[23];
		field.data_size = 8;
		field.name = "reward_amount";
		field.code = {4};
	}
	{
		auto& field = type_code->fields[24];
		field.is_extended = true;
		field.name = "reward_addr";
		field.code = {33, 11, 32, 1};
	}
	{
		auto& field = type_code->fields[25];
		field.is_extended = true;
		field.name = "reward_contract";
		field.code = {33, 11, 32, 1};
	}
	{
		auto& field = type_code->fields[26];
		field.is_extended = true;
		field.name = "reward_account";
		field.code = {33, 11, 32, 1};
	}
	{
		auto& field = type_code->fields[27];
		field.data_size = 1;
		field.name = "reward_vote";
		field.code = {5};
	}
	{
		auto& field = type_code->fields[28];
		field.data_size = 4;
		field.name = "reward_vote_sum";
		field.code = {7};
	}
	{
		auto& field = type_code->fields[29];
		field.data_size = 4;
		field.name = "reward_vote_count";
		field.code = {3};
	}
	{
		auto& field = type_code->fields[30];
		field.data_size = 8;
		field.name = "base_reward";
		field.code = {4};
	}
	{
		auto& field = type_code->fields[31];
		field.data_size = 8;
		field.name = "static_cost";
		field.code = {4};
	}
	{
		auto& field = type_code->fields[32];
		field.data_size = 8;
		field.name = "total_cost";
		field.code = {4};
	}
	{
		auto& field = type_code->fields[33];
		field.data_size = 4;
		field.name = "tx_count";
		field.code = {3};
	}
	{
		auto& field = type_code->fields[34];
		field.data_size = 8;
		field.name = "tx_fees";
		field.code = {4};
	}
	{
		auto& field = type_code->fields[35];
		field.data_size = 8;
		field.name = "txfee_buffer";
		field.code = {4};
	}
	{
		auto& field = type_code->fields[36];
		field.is_extended = true;
		field.name = "tx_hash";
		field.code = {11, 32, 1};
	}
	{
		auto& field = type_code->fields[37];
		field.is_extended = true;
		field.name = "farmer_sig";
		field.code = {33, 11, 64, 1};
	}
	{
		auto& field = type_code->fields[38];
		field.is_extended = true;
		field.name = "content_hash";
		field.code = {11, 32, 1};
	}
	type_code->build();
	return type_code;
}

std::shared_ptr<vnx::Value> BlockHeader::vnx_call_switch(std::shared_ptr<const vnx::Value> _method) {
	switch(_method->get_type_hash()) {
	}
	return nullptr;
}


} // namespace mmx


namespace vnx {

void read(TypeInput& in, ::mmx::BlockHeader& value, const TypeCode* type_code, const uint16_t* code) {
	TypeInput::recursion_t tag(in);
	if(code) {
		switch(code[0]) {
			case CODE_OBJECT:
			case CODE_ALT_OBJECT: {
				Object tmp;
				vnx::read(in, tmp, type_code, code);
				value.from_object(tmp);
				return;
			}
			case CODE_DYNAMIC:
			case CODE_ALT_DYNAMIC:
				vnx::read_dynamic(in, value);
				return;
		}
	}
	if(!type_code) {
		vnx::skip(in, type_code, code);
		return;
	}
	if(code) {
		switch(code[0]) {
			case CODE_STRUCT: type_code = type_code->depends[code[1]]; break;
			case CODE_ALT_STRUCT: type_code = type_code->depends[vnx::flip_bytes(code[1])]; break;
			default: {
				vnx::skip(in, type_code, code);
				return;
			}
		}
	}
	const auto* const _buf = in.read(type_code->total_field_size);
	if(type_code->is_matched) {
		if(const auto* const _field = type_code->field_map[0]) {
			vnx::read_value(_buf + _field->offset, value.version, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[1]) {
			vnx::read_value(_buf + _field->offset, value.support_flags, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[4]) {
			vnx::read_value(_buf + _field->offset, value.height, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[5]) {
			vnx::read_value(_buf + _field->offset, value.vdf_height, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[6]) {
			vnx::read_value(_buf + _field->offset, value.nonce, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[7]) {
			vnx::read_value(_buf + _field->offset, value.time_stamp, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[8]) {
			vnx::read_value(_buf + _field->offset, value.time_diff, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[9]) {
			vnx::read_value(_buf + _field->offset, value.space_diff, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[12]) {
			vnx::read_value(_buf + _field->offset, value.vdf_count, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[13]) {
			vnx::read_value(_buf + _field->offset, value.vdf_iters, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[20]) {
			vnx::read_value(_buf + _field->offset, value.is_space_fork, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[21]) {
			vnx::read_value(_buf + _field->offset, value.space_fork_len, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[22]) {
			vnx::read_value(_buf + _field->offset, value.space_fork_proofs, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[23]) {
			vnx::read_value(_buf + _field->offset, value.reward_amount, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[27]) {
			vnx::read_value(_buf + _field->offset, value.reward_vote, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[28]) {
			vnx::read_value(_buf + _field->offset, value.reward_vote_sum, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[29]) {
			vnx::read_value(_buf + _field->offset, value.reward_vote_count, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[30]) {
			vnx::read_value(_buf + _field->offset, value.base_reward, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[31]) {
			vnx::read_value(_buf + _field->offset, value.static_cost, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[32]) {
			vnx::read_value(_buf + _field->offset, value.total_cost, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[33]) {
			vnx::read_value(_buf + _field->offset, value.tx_count, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[34]) {
			vnx::read_value(_buf + _field->offset, value.tx_fees, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[35]) {
			vnx::read_value(_buf + _field->offset, value.txfee_buffer, _field->code.data());
		}
	}
	for(const auto* _field : type_code->ext_fields) {
		switch(_field->native_index) {
			case 2: vnx::read(in, value.hash, type_code, _field->code.data()); break;
			case 3: vnx::read(in, value.prev, type_code, _field->code.data()); break;
			case 10: vnx::read(in, value.weight, type_code, _field->code.data()); break;
			case 11: vnx::read(in, value.total_weight, type_code, _field->code.data()); break;
			case 14: vnx::read(in, value.vdf_output, type_code, _field->code.data()); break;
			case 15: vnx::read(in, value.vdf_reward_addr, type_code, _field->code.data()); break;
			case 16: vnx::read(in, value.vdf_reward_payout, type_code, _field->code.data()); break;
			case 17: vnx::read(in, value.proof, type_code, _field->code.data()); break;
			case 18: vnx::read(in, value.proof_hash, type_code, _field->code.data()); break;
			case 19: vnx::read(in, value.challenge, type_code, _field->code.data()); break;
			case 24: vnx::read(in, value.reward_addr, type_code, _field->code.data()); break;
			case 25: vnx::read(in, value.reward_contract, type_code, _field->code.data()); break;
			case 26: vnx::read(in, value.reward_account, type_code, _field->code.data()); break;
			case 36: vnx::read(in, value.tx_hash, type_code, _field->code.data()); break;
			case 37: vnx::read(in, value.farmer_sig, type_code, _field->code.data()); break;
			case 38: vnx::read(in, value.content_hash, type_code, _field->code.data()); break;
			default: vnx::skip(in, type_code, _field->code.data());
		}
	}
}

void write(TypeOutput& out, const ::mmx::BlockHeader& value, const TypeCode* type_code, const uint16_t* code) {
	if(code && code[0] == CODE_OBJECT) {
		vnx::write(out, value.to_object(), nullptr, code);
		return;
	}
	if(!type_code || (code && code[0] == CODE_ANY)) {
		type_code = mmx::vnx_native_type_code_BlockHeader;
		out.write_type_code(type_code);
		vnx::write_class_header<::mmx::BlockHeader>(out);
	}
	else if(code && code[0] == CODE_STRUCT) {
		type_code = type_code->depends[code[1]];
	}
	auto* const _buf = out.write(130);
	vnx::write_value(_buf + 0, value.version);
	vnx::write_value(_buf + 4, value.support_flags);
	vnx::write_value(_buf + 8, value.height);
	vnx::write_value(_buf + 12, value.vdf_height);
	vnx::write_value(_buf + 16, value.nonce);
	vnx::write_value(_buf + 24, value.time_stamp);
	vnx::write_value(_buf + 32, value.time_diff);
	vnx::write_value(_buf + 40, value.space_diff);
	vnx::write_value(_buf + 48, value.vdf_count);
	vnx::write_value(_buf + 52, value.vdf_iters);
	vnx::write_value(_buf + 60, value.is_space_fork);
	vnx::write_value(_buf + 61, value.space_fork_len);
	vnx::write_value(_buf + 65, value.space_fork_proofs);
	vnx::write_value(_buf + 69, value.reward_amount);
	vnx::write_value(_buf + 77, value.reward_vote);
	vnx::write_value(_buf + 78, value.reward_vote_sum);
	vnx::write_value(_buf + 82, value.reward_vote_count);
	vnx::write_value(_buf + 86, value.base_reward);
	vnx::write_value(_buf + 94, value.static_cost);
	vnx::write_value(_buf + 102, value.total_cost);
	vnx::write_value(_buf + 110, value.tx_count);
	vnx::write_value(_buf + 114, value.tx_fees);
	vnx::write_value(_buf + 122, value.txfee_buffer);
	vnx::write(out, value.hash, type_code, type_code->fields[2].code.data());
	vnx::write(out, value.prev, type_code, type_code->fields[3].code.data());
	vnx::write(out, value.weight, type_code, type_code->fields[10].code.data());
	vnx::write(out, value.total_weight, type_code, type_code->fields[11].code.data());
	vnx::write(out, value.vdf_output, type_code, type_code->fields[14].code.data());
	vnx::write(out, value.vdf_reward_addr, type_code, type_code->fields[15].code.data());
	vnx::write(out, value.vdf_reward_payout, type_code, type_code->fields[16].code.data());
	vnx::write(out, value.proof, type_code, type_code->fields[17].code.data());
	vnx::write(out, value.proof_hash, type_code, type_code->fields[18].code.data());
	vnx::write(out, value.challenge, type_code, type_code->fields[19].code.data());
	vnx::write(out, value.reward_addr, type_code, type_code->fields[24].code.data());
	vnx::write(out, value.reward_contract, type_code, type_code->fields[25].code.data());
	vnx::write(out, value.reward_account, type_code, type_code->fields[26].code.data());
	vnx::write(out, value.tx_hash, type_code, type_code->fields[36].code.data());
	vnx::write(out, value.farmer_sig, type_code, type_code->fields[37].code.data());
	vnx::write(out, value.content_hash, type_code, type_code->fields[38].code.data());
}

void read(std::istream& in, ::mmx::BlockHeader& value) {
	value.read(in);
}

void write(std::ostream& out, const ::mmx::BlockHeader& value) {
	value.write(out);
}

void accept(Visitor& visitor, const ::mmx::BlockHeader& value) {
	value.accept(visitor);
}

} // vnx
