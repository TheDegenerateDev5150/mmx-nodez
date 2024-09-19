
// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_mmx_swap_entry_t_HXX_
#define INCLUDE_mmx_swap_entry_t_HXX_

#include <vnx/Type.h>
#include <mmx/package.hxx>
#include <mmx/addr_t.hpp>
#include <mmx/hash_t.hpp>


namespace mmx {

struct MMX_EXPORT swap_entry_t : vnx::struct_t {
	
	
	uint32_t height = 0;
	::mmx::hash_t txid;
	std::string type;
	uint8_t index = 0;
	uint64_t amount = 0;
	vnx::optional<vnx::float64_t> value;
	vnx::optional<std::string> symbol;
	vnx::optional<::mmx::addr_t> user;
	
	static const vnx::Hash64 VNX_TYPE_HASH;
	static const vnx::Hash64 VNX_CODE_HASH;
	
	static constexpr uint64_t VNX_TYPE_ID = 0xe3110712aa0f6064ull;
	
	swap_entry_t() {}
	
	vnx::Hash64 get_type_hash() const;
	std::string get_type_name() const;
	const vnx::TypeCode* get_type_code() const;
	
	static std::shared_ptr<swap_entry_t> create();
	std::shared_ptr<swap_entry_t> clone() const;
	
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
	
	friend std::ostream& operator<<(std::ostream& _out, const swap_entry_t& _value);
	friend std::istream& operator>>(std::istream& _in, swap_entry_t& _value);
	
	static const vnx::TypeCode* static_get_type_code();
	static std::shared_ptr<vnx::TypeCode> static_create_type_code();
	
};

template<typename T>
void swap_entry_t::accept_generic(T& _visitor) const {
	_visitor.template type_begin<swap_entry_t>(8);
	_visitor.type_field("height", 0); _visitor.accept(height);
	_visitor.type_field("txid", 1); _visitor.accept(txid);
	_visitor.type_field("type", 2); _visitor.accept(type);
	_visitor.type_field("index", 3); _visitor.accept(index);
	_visitor.type_field("amount", 4); _visitor.accept(amount);
	_visitor.type_field("value", 5); _visitor.accept(value);
	_visitor.type_field("symbol", 6); _visitor.accept(symbol);
	_visitor.type_field("user", 7); _visitor.accept(user);
	_visitor.template type_end<swap_entry_t>(8);
}


} // namespace mmx


namespace vnx {

template<>
struct is_equivalent<::mmx::swap_entry_t> {
	bool operator()(const uint16_t* code, const TypeCode* type_code);
};

} // vnx

#endif // INCLUDE_mmx_swap_entry_t_HXX_
