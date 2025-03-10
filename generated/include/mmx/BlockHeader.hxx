
// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_mmx_BlockHeader_HXX_
#define INCLUDE_mmx_BlockHeader_HXX_

#include <mmx/package.hxx>
#include <mmx/ChainParams.hxx>
#include <mmx/ProofOfSpace.hxx>
#include <mmx/addr_t.hpp>
#include <mmx/block_index_t.hxx>
#include <mmx/hash_t.hpp>
#include <mmx/pubkey_t.hpp>
#include <mmx/signature_t.hpp>
#include <mmx/uint128.hpp>
#include <vnx/Value.h>


namespace mmx {

class MMX_EXPORT BlockHeader : public ::vnx::Value {
public:
	static const uint32_t SUPPORT_HARDFORK1 = 0x1;
	
	uint32_t version = 0;
	uint32_t support_flags = 0;
	::mmx::hash_t hash;
	::mmx::hash_t prev;
	uint32_t height = 0;
	uint32_t vdf_height = 0;
	uint64_t nonce = 0;
	int64_t time_stamp = 0;
	uint64_t time_diff = 0;
	uint64_t space_diff = 0;
	::mmx::uint128 weight;
	::mmx::uint128 total_weight;
	uint32_t vdf_count = 0;
	uint64_t vdf_iters = 0;
	::mmx::hash_t vdf_output;
	std::vector<::mmx::addr_t> vdf_reward_addr;
	vnx::optional<::mmx::addr_t> vdf_reward_payout;
	std::vector<std::shared_ptr<const ::mmx::ProofOfSpace>> proof;
	::mmx::hash_t proof_hash;
	::mmx::hash_t challenge;
	vnx::bool_t is_space_fork = 0;
	uint32_t space_fork_len = 0;
	uint32_t space_fork_proofs = 0;
	uint64_t reward_amount = 0;
	vnx::optional<::mmx::addr_t> reward_addr;
	vnx::optional<::mmx::addr_t> reward_contract;
	vnx::optional<::mmx::addr_t> reward_account;
	int8_t reward_vote = 0;
	int32_t reward_vote_sum = 0;
	uint32_t reward_vote_count = 0;
	uint64_t base_reward = 0;
	::mmx::addr_t project_addr;
	uint64_t static_cost = 0;
	uint64_t total_cost = 0;
	uint32_t tx_count = 0;
	uint64_t tx_fees = 0;
	uint64_t txfee_buffer = 0;
	::mmx::hash_t tx_hash;
	vnx::optional<::mmx::signature_t> farmer_sig;
	::mmx::hash_t content_hash;
	
	typedef ::vnx::Value Super;
	
	static const vnx::Hash64 VNX_TYPE_HASH;
	static const vnx::Hash64 VNX_CODE_HASH;
	
	static constexpr uint64_t VNX_TYPE_ID = 0xcaae941a2fc712a6ull;
	
	BlockHeader() {}
	
	vnx::Hash64 get_type_hash() const override;
	std::string get_type_name() const override;
	const vnx::TypeCode* get_type_code() const override;
	
	virtual vnx::bool_t is_valid() const;
	virtual ::mmx::hash_t calc_hash() const;
	virtual ::mmx::hash_t calc_content_hash() const;
	virtual void validate() const;
	virtual std::shared_ptr<const ::mmx::BlockHeader> get_header() const;
	virtual ::mmx::pubkey_t get_farmer_key() const;
	virtual ::mmx::block_index_t get_block_index(const int64_t& file_offset = 0) const;
	virtual void set_space_diff(std::shared_ptr<const ::mmx::ChainParams> params = nullptr, std::shared_ptr<const ::mmx::BlockHeader> prev = nullptr);
	virtual void set_base_reward(std::shared_ptr<const ::mmx::ChainParams> params = nullptr, std::shared_ptr<const ::mmx::BlockHeader> prev = nullptr);
	
	static std::shared_ptr<BlockHeader> create();
	std::shared_ptr<vnx::Value> clone() const override;
	
	void read(vnx::TypeInput& _in, const vnx::TypeCode* _type_code, const uint16_t* _code) override;
	void write(vnx::TypeOutput& _out, const vnx::TypeCode* _type_code, const uint16_t* _code) const override;
	
	void read(std::istream& _in) override;
	void write(std::ostream& _out) const override;
	
	template<typename T>
	void accept_generic(T& _visitor) const;
	void accept(vnx::Visitor& _visitor) const override;
	
	vnx::Object to_object() const override;
	void from_object(const vnx::Object& object) override;
	
	vnx::Variant get_field(const std::string& name) const override;
	void set_field(const std::string& name, const vnx::Variant& value) override;
	
	friend std::ostream& operator<<(std::ostream& _out, const BlockHeader& _value);
	friend std::istream& operator>>(std::istream& _in, BlockHeader& _value);
	
	static const vnx::TypeCode* static_get_type_code();
	static std::shared_ptr<vnx::TypeCode> static_create_type_code();
	
protected:
	std::shared_ptr<vnx::Value> vnx_call_switch(std::shared_ptr<const vnx::Value> _method) override;
	
};

template<typename T>
void BlockHeader::accept_generic(T& _visitor) const {
	_visitor.template type_begin<BlockHeader>(40);
	_visitor.type_field("version", 0); _visitor.accept(version);
	_visitor.type_field("support_flags", 1); _visitor.accept(support_flags);
	_visitor.type_field("hash", 2); _visitor.accept(hash);
	_visitor.type_field("prev", 3); _visitor.accept(prev);
	_visitor.type_field("height", 4); _visitor.accept(height);
	_visitor.type_field("vdf_height", 5); _visitor.accept(vdf_height);
	_visitor.type_field("nonce", 6); _visitor.accept(nonce);
	_visitor.type_field("time_stamp", 7); _visitor.accept(time_stamp);
	_visitor.type_field("time_diff", 8); _visitor.accept(time_diff);
	_visitor.type_field("space_diff", 9); _visitor.accept(space_diff);
	_visitor.type_field("weight", 10); _visitor.accept(weight);
	_visitor.type_field("total_weight", 11); _visitor.accept(total_weight);
	_visitor.type_field("vdf_count", 12); _visitor.accept(vdf_count);
	_visitor.type_field("vdf_iters", 13); _visitor.accept(vdf_iters);
	_visitor.type_field("vdf_output", 14); _visitor.accept(vdf_output);
	_visitor.type_field("vdf_reward_addr", 15); _visitor.accept(vdf_reward_addr);
	_visitor.type_field("vdf_reward_payout", 16); _visitor.accept(vdf_reward_payout);
	_visitor.type_field("proof", 17); _visitor.accept(proof);
	_visitor.type_field("proof_hash", 18); _visitor.accept(proof_hash);
	_visitor.type_field("challenge", 19); _visitor.accept(challenge);
	_visitor.type_field("is_space_fork", 20); _visitor.accept(is_space_fork);
	_visitor.type_field("space_fork_len", 21); _visitor.accept(space_fork_len);
	_visitor.type_field("space_fork_proofs", 22); _visitor.accept(space_fork_proofs);
	_visitor.type_field("reward_amount", 23); _visitor.accept(reward_amount);
	_visitor.type_field("reward_addr", 24); _visitor.accept(reward_addr);
	_visitor.type_field("reward_contract", 25); _visitor.accept(reward_contract);
	_visitor.type_field("reward_account", 26); _visitor.accept(reward_account);
	_visitor.type_field("reward_vote", 27); _visitor.accept(reward_vote);
	_visitor.type_field("reward_vote_sum", 28); _visitor.accept(reward_vote_sum);
	_visitor.type_field("reward_vote_count", 29); _visitor.accept(reward_vote_count);
	_visitor.type_field("base_reward", 30); _visitor.accept(base_reward);
	_visitor.type_field("project_addr", 31); _visitor.accept(project_addr);
	_visitor.type_field("static_cost", 32); _visitor.accept(static_cost);
	_visitor.type_field("total_cost", 33); _visitor.accept(total_cost);
	_visitor.type_field("tx_count", 34); _visitor.accept(tx_count);
	_visitor.type_field("tx_fees", 35); _visitor.accept(tx_fees);
	_visitor.type_field("txfee_buffer", 36); _visitor.accept(txfee_buffer);
	_visitor.type_field("tx_hash", 37); _visitor.accept(tx_hash);
	_visitor.type_field("farmer_sig", 38); _visitor.accept(farmer_sig);
	_visitor.type_field("content_hash", 39); _visitor.accept(content_hash);
	_visitor.template type_end<BlockHeader>(40);
}


} // namespace mmx


namespace vnx {

} // vnx

#endif // INCLUDE_mmx_BlockHeader_HXX_
