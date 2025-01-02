
// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_mmx_spend_options_t_HXX_
#define INCLUDE_mmx_spend_options_t_HXX_

#include <vnx/Type.h>
#include <mmx/package.hxx>
#include <mmx/Contract.hxx>
#include <mmx/addr_t.hpp>
#include <mmx/tx_note_e.hxx>


namespace mmx {

struct MMX_EXPORT spend_options_t : vnx::struct_t {
	
	
	vnx::bool_t auto_send = true;
	vnx::bool_t mark_spent = false;
	uint32_t fee_ratio = 1024;
	uint32_t gas_limit = 5000000;
	vnx::optional<uint32_t> expire_at;
	vnx::optional<uint32_t> expire_delta;
	vnx::optional<uint64_t> nonce;
	vnx::optional<::mmx::addr_t> user;
	vnx::optional<::mmx::addr_t> sender;
	vnx::optional<std::string> passphrase;
	vnx::optional<::mmx::tx_note_e> note;
	vnx::optional<std::string> memo;
	std::map<::mmx::addr_t, ::mmx::addr_t> owner_map;
	std::map<::mmx::addr_t, std::shared_ptr<const ::mmx::Contract>> contract_map;
	
	static const vnx::Hash64 VNX_TYPE_HASH;
	static const vnx::Hash64 VNX_CODE_HASH;
	
	static constexpr uint64_t VNX_TYPE_ID = 0x37f7c6d377362e95ull;
	
	spend_options_t() {}
	
	vnx::Hash64 get_type_hash() const;
	std::string get_type_name() const;
	const vnx::TypeCode* get_type_code() const;
	
	static std::shared_ptr<spend_options_t> create();
	std::shared_ptr<spend_options_t> clone() const;
	
	void read(vnx::TypeInput& _in, const vnx::TypeCode* _type_code, const uint16_t* _code);
	void write(vnx::TypeOutput& _out, const vnx::TypeCode* _type_code, const uint16_t* _code) const;
	
	void read(std::istream& _in);
	void write(std::ostream& _out) const;
	
	template<typename T>
	void accept_generic(T& _visitor) const;
	void accept(vnx::Visitor& _visitor) const;
	
	vnx::Object to_object() const;
	void from_object(const vnx::Object& object);
	
	vnx::Variant get_field(const std::string& name) const;
	void set_field(const std::string& name, const vnx::Variant& value);
	
	friend std::ostream& operator<<(std::ostream& _out, const spend_options_t& _value);
	friend std::istream& operator>>(std::istream& _in, spend_options_t& _value);
	
	static const vnx::TypeCode* static_get_type_code();
	static std::shared_ptr<vnx::TypeCode> static_create_type_code();
	
};

template<typename T>
void spend_options_t::accept_generic(T& _visitor) const {
	_visitor.template type_begin<spend_options_t>(14);
	_visitor.type_field("auto_send", 0); _visitor.accept(auto_send);
	_visitor.type_field("mark_spent", 1); _visitor.accept(mark_spent);
	_visitor.type_field("fee_ratio", 2); _visitor.accept(fee_ratio);
	_visitor.type_field("gas_limit", 3); _visitor.accept(gas_limit);
	_visitor.type_field("expire_at", 4); _visitor.accept(expire_at);
	_visitor.type_field("expire_delta", 5); _visitor.accept(expire_delta);
	_visitor.type_field("nonce", 6); _visitor.accept(nonce);
	_visitor.type_field("user", 7); _visitor.accept(user);
	_visitor.type_field("sender", 8); _visitor.accept(sender);
	_visitor.type_field("passphrase", 9); _visitor.accept(passphrase);
	_visitor.type_field("note", 10); _visitor.accept(note);
	_visitor.type_field("memo", 11); _visitor.accept(memo);
	_visitor.type_field("owner_map", 12); _visitor.accept(owner_map);
	_visitor.type_field("contract_map", 13); _visitor.accept(contract_map);
	_visitor.template type_end<spend_options_t>(14);
}


} // namespace mmx


namespace vnx {

template<>
struct is_equivalent<::mmx::spend_options_t> {
	bool operator()(const uint16_t* code, const TypeCode* type_code);
};

} // vnx

#endif // INCLUDE_mmx_spend_options_t_HXX_
