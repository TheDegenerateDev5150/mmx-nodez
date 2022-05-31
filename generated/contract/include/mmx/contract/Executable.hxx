
// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_mmx_contract_Executable_HXX_
#define INCLUDE_mmx_contract_Executable_HXX_

#include <mmx/contract/package.hxx>
#include <mmx/ChainParams.hxx>
#include <mmx/Context.hxx>
#include <mmx/Operation.hxx>
#include <mmx/addr_t.hpp>
#include <mmx/contract/TokenBase.hxx>
#include <mmx/contract/method_t.hxx>
#include <mmx/hash_t.hpp>
#include <mmx/txout_t.hxx>
#include <vnx/Variant.hpp>


namespace mmx {
namespace contract {

class MMX_CONTRACT_EXPORT Executable : public ::mmx::contract::TokenBase {
public:
	
	std::map<std::string, uint32_t> fields;
	std::map<std::string, ::mmx::contract::method_t> methods;
	std::map<std::string, ::mmx::addr_t> depends;
	std::vector<uint8_t> constant;
	std::vector<uint8_t> binary;
	vnx::optional<::mmx::addr_t> source;
	std::string init_method;
	std::vector<::vnx::Variant> init_args;
	
	typedef ::mmx::contract::TokenBase Super;
	
	static const vnx::Hash64 VNX_TYPE_HASH;
	static const vnx::Hash64 VNX_CODE_HASH;
	
	static constexpr uint64_t VNX_TYPE_ID = 0xfa6a3ac9103ebb12ull;
	
	Executable() {}
	
	vnx::Hash64 get_type_hash() const override;
	std::string get_type_name() const override;
	const vnx::TypeCode* get_type_code() const override;
	
	virtual vnx::bool_t is_valid() const override;
	virtual ::mmx::hash_t calc_hash() const override;
	virtual uint64_t calc_cost(std::shared_ptr<const ::mmx::ChainParams> params = nullptr) const override;
	virtual std::vector<::mmx::txout_t> validate(std::shared_ptr<const ::mmx::Operation> operation = nullptr, std::shared_ptr<const ::mmx::Context> context = nullptr) const;
	
	static std::shared_ptr<Executable> create();
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
	
	friend std::ostream& operator<<(std::ostream& _out, const Executable& _value);
	friend std::istream& operator>>(std::istream& _in, Executable& _value);
	
	static const vnx::TypeCode* static_get_type_code();
	static std::shared_ptr<vnx::TypeCode> static_create_type_code();
	
protected:
	std::shared_ptr<vnx::Value> vnx_call_switch(std::shared_ptr<const vnx::Value> _method) override;
	
};

template<typename T>
void Executable::accept_generic(T& _visitor) const {
	_visitor.template type_begin<Executable>(14);
	_visitor.type_field("version", 0); _visitor.accept(version);
	_visitor.type_field("name", 1); _visitor.accept(name);
	_visitor.type_field("symbol", 2); _visitor.accept(symbol);
	_visitor.type_field("web_url", 3); _visitor.accept(web_url);
	_visitor.type_field("icon_url", 4); _visitor.accept(icon_url);
	_visitor.type_field("decimals", 5); _visitor.accept(decimals);
	_visitor.type_field("fields", 6); _visitor.accept(fields);
	_visitor.type_field("methods", 7); _visitor.accept(methods);
	_visitor.type_field("depends", 8); _visitor.accept(depends);
	_visitor.type_field("constant", 9); _visitor.accept(constant);
	_visitor.type_field("binary", 10); _visitor.accept(binary);
	_visitor.type_field("source", 11); _visitor.accept(source);
	_visitor.type_field("init_method", 12); _visitor.accept(init_method);
	_visitor.type_field("init_args", 13); _visitor.accept(init_args);
	_visitor.template type_end<Executable>(14);
}


} // namespace mmx
} // namespace contract


namespace vnx {

} // vnx

#endif // INCLUDE_mmx_contract_Executable_HXX_
