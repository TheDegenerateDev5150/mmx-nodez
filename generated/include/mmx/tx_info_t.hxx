
// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_mmx_tx_info_t_HXX_
#define INCLUDE_mmx_tx_info_t_HXX_

#include <mmx/package.hxx>
#include <mmx/Contract.hxx>
#include <mmx/Operation.hxx>
#include <mmx/addr_t.hpp>
#include <mmx/hash_t.hpp>
#include <mmx/tx_note_e.hxx>
#include <mmx/txin_t.hxx>
#include <mmx/txout_t.hxx>
#include <mmx/uint128.hpp>
#include <vnx/Value.h>


namespace mmx {

class MMX_EXPORT tx_info_t : public ::vnx::Value {
public:
	
	::mmx::hash_t id;
	uint32_t expires = 0;
	vnx::bool_t did_fail = 0;
	vnx::optional<uint32_t> height;
	vnx::optional<int64_t> time_stamp;
	vnx::optional<::mmx::hash_t> block;
	vnx::optional<std::string> message;
	uint32_t fee = 0;
	uint32_t cost = 0;
	::mmx::tx_note_e note;
	vnx::optional<::mmx::addr_t> sender;
	std::vector<::mmx::txin_t> inputs;
	std::vector<::mmx::txout_t> outputs;
	std::vector<std::shared_ptr<const ::mmx::Operation>> operations;
	std::shared_ptr<const ::mmx::Contract> deployed;
	std::map<::mmx::addr_t, ::mmx::uint128> input_amounts;
	std::map<::mmx::addr_t, ::mmx::uint128> output_amounts;
	std::map<::mmx::addr_t, std::shared_ptr<const ::mmx::Contract>> contracts;
	
	typedef ::vnx::Value Super;
	
	static const vnx::Hash64 VNX_TYPE_HASH;
	static const vnx::Hash64 VNX_CODE_HASH;
	
	static constexpr uint64_t VNX_TYPE_ID = 0x44e4a710953f4785ull;
	
	tx_info_t() {}
	
	vnx::Hash64 get_type_hash() const override;
	std::string get_type_name() const override;
	const vnx::TypeCode* get_type_code() const override;
	
	static std::shared_ptr<tx_info_t> create();
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
	
	friend std::ostream& operator<<(std::ostream& _out, const tx_info_t& _value);
	friend std::istream& operator>>(std::istream& _in, tx_info_t& _value);
	
	static const vnx::TypeCode* static_get_type_code();
	static std::shared_ptr<vnx::TypeCode> static_create_type_code();
	
protected:
	std::shared_ptr<vnx::Value> vnx_call_switch(std::shared_ptr<const vnx::Value> _method) override;
	
};

template<typename T>
void tx_info_t::accept_generic(T& _visitor) const {
	_visitor.template type_begin<tx_info_t>(18);
	_visitor.type_field("id", 0); _visitor.accept(id);
	_visitor.type_field("expires", 1); _visitor.accept(expires);
	_visitor.type_field("did_fail", 2); _visitor.accept(did_fail);
	_visitor.type_field("height", 3); _visitor.accept(height);
	_visitor.type_field("time_stamp", 4); _visitor.accept(time_stamp);
	_visitor.type_field("block", 5); _visitor.accept(block);
	_visitor.type_field("message", 6); _visitor.accept(message);
	_visitor.type_field("fee", 7); _visitor.accept(fee);
	_visitor.type_field("cost", 8); _visitor.accept(cost);
	_visitor.type_field("note", 9); _visitor.accept(note);
	_visitor.type_field("sender", 10); _visitor.accept(sender);
	_visitor.type_field("inputs", 11); _visitor.accept(inputs);
	_visitor.type_field("outputs", 12); _visitor.accept(outputs);
	_visitor.type_field("operations", 13); _visitor.accept(operations);
	_visitor.type_field("deployed", 14); _visitor.accept(deployed);
	_visitor.type_field("input_amounts", 15); _visitor.accept(input_amounts);
	_visitor.type_field("output_amounts", 16); _visitor.accept(output_amounts);
	_visitor.type_field("contracts", 17); _visitor.accept(contracts);
	_visitor.template type_end<tx_info_t>(18);
}


} // namespace mmx


namespace vnx {

} // vnx

#endif // INCLUDE_mmx_tx_info_t_HXX_
