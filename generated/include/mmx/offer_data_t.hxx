
// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_mmx_offer_data_t_HXX_
#define INCLUDE_mmx_offer_data_t_HXX_

#include <vnx/Type.h>
#include <mmx/package.hxx>
#include <mmx/addr_t.hpp>
#include <mmx/uint128.hpp>


namespace mmx {

struct MMX_EXPORT offer_data_t {
	
	
	uint32_t height = 0;
	::mmx::addr_t address;
	::mmx::addr_t bid_currency;
	::mmx::addr_t ask_currency;
	uint64_t bid_balance = 0;
	uint64_t ask_balance = 0;
	::mmx::uint128 inv_price;
	vnx::float64_t price = 0;
	
	static const vnx::Hash64 VNX_TYPE_HASH;
	static const vnx::Hash64 VNX_CODE_HASH;
	
	static constexpr uint64_t VNX_TYPE_ID = 0xc97a08a709a5f1efull;
	
	offer_data_t() {}
	
	vnx::Hash64 get_type_hash() const;
	std::string get_type_name() const;
	const vnx::TypeCode* get_type_code() const;
	
	vnx::bool_t is_scam() const;
	
	static std::shared_ptr<offer_data_t> create();
	std::shared_ptr<offer_data_t> clone() const;
	
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
	
	friend std::ostream& operator<<(std::ostream& _out, const offer_data_t& _value);
	friend std::istream& operator>>(std::istream& _in, offer_data_t& _value);
	
	static const vnx::TypeCode* static_get_type_code();
	static std::shared_ptr<vnx::TypeCode> static_create_type_code();
	
};

template<typename T>
void offer_data_t::accept_generic(T& _visitor) const {
	_visitor.template type_begin<offer_data_t>(8);
	_visitor.type_field("height", 0); _visitor.accept(height);
	_visitor.type_field("address", 1); _visitor.accept(address);
	_visitor.type_field("bid_currency", 2); _visitor.accept(bid_currency);
	_visitor.type_field("ask_currency", 3); _visitor.accept(ask_currency);
	_visitor.type_field("bid_balance", 4); _visitor.accept(bid_balance);
	_visitor.type_field("ask_balance", 5); _visitor.accept(ask_balance);
	_visitor.type_field("inv_price", 6); _visitor.accept(inv_price);
	_visitor.type_field("price", 7); _visitor.accept(price);
	_visitor.template type_end<offer_data_t>(8);
}


} // namespace mmx


namespace vnx {

template<>
struct is_equivalent<::mmx::offer_data_t> {
	bool operator()(const uint16_t* code, const TypeCode* type_code);
};

} // vnx

#endif // INCLUDE_mmx_offer_data_t_HXX_
