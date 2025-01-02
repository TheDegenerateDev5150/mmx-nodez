
// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_mmx_contract_TokenBase_HXX_
#define INCLUDE_mmx_contract_TokenBase_HXX_

#include <mmx/contract/package.hxx>
#include <mmx/Contract.hxx>
#include <mmx/addr_t.hpp>
#include <mmx/hash_t.hpp>
#include <vnx/Variant.hpp>


namespace mmx {
namespace contract {

class MMX_CONTRACT_EXPORT TokenBase : public ::mmx::Contract {
public:
	
	std::string name;
	std::string symbol;
	int32_t decimals = 0;
	::vnx::Variant meta_data;
	
	typedef ::mmx::Contract Super;
	
	static const vnx::Hash64 VNX_TYPE_HASH;
	static const vnx::Hash64 VNX_CODE_HASH;
	
	static constexpr uint64_t VNX_TYPE_ID = 0x5aeed4c96d232b5eull;
	
	TokenBase() {}
	
	vnx::Hash64 get_type_hash() const override;
	std::string get_type_name() const override;
	const vnx::TypeCode* get_type_code() const override;
	
	virtual vnx::bool_t is_valid() const override;
	virtual ::mmx::hash_t calc_hash(const vnx::bool_t& full_hash = 0) const override;
	virtual uint64_t num_bytes() const override;
	
	static std::shared_ptr<TokenBase> create();
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
	
	friend std::ostream& operator<<(std::ostream& _out, const TokenBase& _value);
	friend std::istream& operator>>(std::istream& _in, TokenBase& _value);
	
	static const vnx::TypeCode* static_get_type_code();
	static std::shared_ptr<vnx::TypeCode> static_create_type_code();
	
protected:
	std::shared_ptr<vnx::Value> vnx_call_switch(std::shared_ptr<const vnx::Value> _method) override;
	
};

template<typename T>
void TokenBase::accept_generic(T& _visitor) const {
	_visitor.template type_begin<TokenBase>(5);
	_visitor.type_field("version", 0); _visitor.accept(version);
	_visitor.type_field("name", 1); _visitor.accept(name);
	_visitor.type_field("symbol", 2); _visitor.accept(symbol);
	_visitor.type_field("decimals", 3); _visitor.accept(decimals);
	_visitor.type_field("meta_data", 4); _visitor.accept(meta_data);
	_visitor.template type_end<TokenBase>(5);
}


} // namespace mmx
} // namespace contract


namespace vnx {

} // vnx

#endif // INCLUDE_mmx_contract_TokenBase_HXX_
