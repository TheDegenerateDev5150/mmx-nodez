
// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_mmx_contract_Token_validate_return_HXX_
#define INCLUDE_mmx_contract_Token_validate_return_HXX_

#include <mmx/contract/package.hxx>
#include <mmx/txout_t.hxx>
#include <vnx/Value.h>


namespace mmx {
namespace contract {

class MMX_CONTRACT_EXPORT Token_validate_return : public ::vnx::Value {
public:
	
	std::vector<::mmx::txout_t> _ret_0;
	
	typedef ::vnx::Value Super;
	
	static const vnx::Hash64 VNX_TYPE_HASH;
	static const vnx::Hash64 VNX_CODE_HASH;
	
	static constexpr uint64_t VNX_TYPE_ID = 0xc7dc19b4d86f2ca1ull;
	
	Token_validate_return() {}
	
	vnx::Hash64 get_type_hash() const override;
	std::string get_type_name() const override;
	const vnx::TypeCode* get_type_code() const override;
	
	static std::shared_ptr<Token_validate_return> create();
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
	
	friend std::ostream& operator<<(std::ostream& _out, const Token_validate_return& _value);
	friend std::istream& operator>>(std::istream& _in, Token_validate_return& _value);
	
	static const vnx::TypeCode* static_get_type_code();
	static std::shared_ptr<vnx::TypeCode> static_create_type_code();
	
};

template<typename T>
void Token_validate_return::accept_generic(T& _visitor) const {
	_visitor.template type_begin<Token_validate_return>(1);
	_visitor.type_field("_ret_0", 0); _visitor.accept(_ret_0);
	_visitor.template type_end<Token_validate_return>(1);
}


} // namespace mmx
} // namespace contract


namespace vnx {

} // vnx

#endif // INCLUDE_mmx_contract_Token_validate_return_HXX_
