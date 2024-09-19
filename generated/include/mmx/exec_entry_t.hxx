
// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_mmx_exec_entry_t_HXX_
#define INCLUDE_mmx_exec_entry_t_HXX_

#include <vnx/Type.h>
#include <mmx/package.hxx>
#include <mmx/addr_t.hpp>
#include <mmx/hash_t.hpp>
#include <vnx/Variant.hpp>


namespace mmx {

struct MMX_EXPORT exec_entry_t : vnx::struct_t {
	
	
	uint32_t height = 0;
	::mmx::hash_t txid;
	std::string method;
	std::vector<::vnx::Variant> args;
	vnx::optional<::mmx::addr_t> user;
	vnx::optional<std::pair<::mmx::addr_t, uint64_t>> deposit;
	
	static const vnx::Hash64 VNX_TYPE_HASH;
	static const vnx::Hash64 VNX_CODE_HASH;
	
	static constexpr uint64_t VNX_TYPE_ID = 0xd30282844b1862a4ull;
	
	exec_entry_t() {}
	
	vnx::Hash64 get_type_hash() const;
	std::string get_type_name() const;
	const vnx::TypeCode* get_type_code() const;
	
	static std::shared_ptr<exec_entry_t> create();
	std::shared_ptr<exec_entry_t> clone() const;
	
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
	
	friend std::ostream& operator<<(std::ostream& _out, const exec_entry_t& _value);
	friend std::istream& operator>>(std::istream& _in, exec_entry_t& _value);
	
	static const vnx::TypeCode* static_get_type_code();
	static std::shared_ptr<vnx::TypeCode> static_create_type_code();
	
};

template<typename T>
void exec_entry_t::accept_generic(T& _visitor) const {
	_visitor.template type_begin<exec_entry_t>(6);
	_visitor.type_field("height", 0); _visitor.accept(height);
	_visitor.type_field("txid", 1); _visitor.accept(txid);
	_visitor.type_field("method", 2); _visitor.accept(method);
	_visitor.type_field("args", 3); _visitor.accept(args);
	_visitor.type_field("user", 4); _visitor.accept(user);
	_visitor.type_field("deposit", 5); _visitor.accept(deposit);
	_visitor.template type_end<exec_entry_t>(6);
}


} // namespace mmx


namespace vnx {

template<>
struct is_equivalent<::mmx::exec_entry_t> {
	bool operator()(const uint16_t* code, const TypeCode* type_code);
};

} // vnx

#endif // INCLUDE_mmx_exec_entry_t_HXX_
