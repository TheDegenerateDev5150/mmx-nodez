
// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_mmx_VDF_Point_HXX_
#define INCLUDE_mmx_VDF_Point_HXX_

#include <mmx/package.hxx>
#include <mmx/ProofOfTime.hxx>
#include <mmx/addr_t.hpp>
#include <mmx/hash_t.hpp>
#include <vnx/Value.h>


namespace mmx {

class MMX_EXPORT VDF_Point : public ::vnx::Value {
public:
	
	uint32_t vdf_height = 0;
	uint64_t start = 0;
	uint64_t num_iters = 0;
	::mmx::hash_t input;
	::mmx::hash_t output;
	::mmx::hash_t prev;
	::mmx::addr_t reward_addr;
	::mmx::hash_t content_hash;
	int64_t recv_time = 0;
	std::shared_ptr<const ::mmx::ProofOfTime> proof;
	
	typedef ::vnx::Value Super;
	
	static const vnx::Hash64 VNX_TYPE_HASH;
	static const vnx::Hash64 VNX_CODE_HASH;
	
	static constexpr uint64_t VNX_TYPE_ID = 0x1671551501b6c956ull;
	
	VDF_Point() {}
	
	vnx::Hash64 get_type_hash() const override;
	std::string get_type_name() const override;
	const vnx::TypeCode* get_type_code() const override;
	
	virtual vnx::bool_t is_valid() const;
	virtual ::mmx::hash_t calc_hash() const;
	
	static std::shared_ptr<VDF_Point> create();
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
	
	friend std::ostream& operator<<(std::ostream& _out, const VDF_Point& _value);
	friend std::istream& operator>>(std::istream& _in, VDF_Point& _value);
	
	static const vnx::TypeCode* static_get_type_code();
	static std::shared_ptr<vnx::TypeCode> static_create_type_code();
	
protected:
	std::shared_ptr<vnx::Value> vnx_call_switch(std::shared_ptr<const vnx::Value> _method) override;
	
};

template<typename T>
void VDF_Point::accept_generic(T& _visitor) const {
	_visitor.template type_begin<VDF_Point>(10);
	_visitor.type_field("vdf_height", 0); _visitor.accept(vdf_height);
	_visitor.type_field("start", 1); _visitor.accept(start);
	_visitor.type_field("num_iters", 2); _visitor.accept(num_iters);
	_visitor.type_field("input", 3); _visitor.accept(input);
	_visitor.type_field("output", 4); _visitor.accept(output);
	_visitor.type_field("prev", 5); _visitor.accept(prev);
	_visitor.type_field("reward_addr", 6); _visitor.accept(reward_addr);
	_visitor.type_field("content_hash", 7); _visitor.accept(content_hash);
	_visitor.type_field("recv_time", 8); _visitor.accept(recv_time);
	_visitor.type_field("proof", 9); _visitor.accept(proof);
	_visitor.template type_end<VDF_Point>(10);
}


} // namespace mmx


namespace vnx {

} // vnx

#endif // INCLUDE_mmx_VDF_Point_HXX_
