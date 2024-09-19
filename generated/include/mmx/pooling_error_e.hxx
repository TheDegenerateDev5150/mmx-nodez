
// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_mmx_pooling_error_e_HXX_
#define INCLUDE_mmx_pooling_error_e_HXX_

#include <vnx/Type.h>
#include <mmx/package.hxx>


namespace mmx {

struct MMX_EXPORT pooling_error_e {
	
	enum enum_t : uint32_t {
		CHALLENGE_NOT_FOUND = 3l,
		CHALLENGE_REVERTED = 1l,
		INVALID_ACCOUNT = 13l,
		INVALID_AUTH_KEY = 12l,
		INVALID_CONTRACT = 9l,
		INVALID_DIFFICULTY = 6l,
		INVALID_PROOF = 4l,
		INVALID_SIGNATURE = 7l,
		INVALID_TIMESTAMP = 15l,
		NONE = 0l,
		PARTIAL_TOO_LATE = 2l,
		POOL_LOST_SYNC = 16l,
		PROOF_NOT_GOOD_ENOUGH = 5l,
		SERVER_ERROR = 8l,
		UNKNOWN_FARMER = 10l,
	};
	
	::mmx::pooling_error_e::enum_t value = ::mmx::pooling_error_e::enum_t(0);
	
	static const vnx::Hash64 VNX_TYPE_HASH;
	static const vnx::Hash64 VNX_CODE_HASH;
	
	static constexpr uint64_t VNX_TYPE_ID = 0xec786b877a93f17ull;
	
	pooling_error_e() {}
	
	pooling_error_e(const enum_t& _value) { value = _value; }
	pooling_error_e(const ::mmx::pooling_error_e& _other) { value = _other.value; }
	
	vnx::Hash64 get_type_hash() const;
	std::string get_type_name() const;
	const vnx::TypeCode* get_type_code() const;
	
	operator enum_t() const { return value; }
	pooling_error_e& operator=(const enum_t& _value) { value = _value; return *this; }
	pooling_error_e& operator=(const ::mmx::pooling_error_e& _other) { value = _other.value; return *this; }
	
	static std::shared_ptr<pooling_error_e> create();
	std::shared_ptr<pooling_error_e> clone() const;
	
	void read(vnx::TypeInput& _in, const vnx::TypeCode* _type_code, const uint16_t* _code);
	void write(vnx::TypeOutput& _out, const vnx::TypeCode* _type_code, const uint16_t* _code) const;
	
	void read(std::istream& _in);
	void write(std::ostream& _out) const;
	
	template<typename T>
	void accept_generic(T& _visitor) const;
	void accept(vnx::Visitor& _visitor) const;
	
	vnx::bool_t is_valid() const;
	std::string to_string() const;
	std::string to_string_value() const;
	std::string to_string_value_full() const;
	
	void from_string(const std::string& str);
	void from_string_value(const std::string& name);
	
	vnx::Object to_object() const;
	void from_object(const vnx::Object& object);
	
	vnx::Variant get_field(const std::string& name) const;
	void set_field(const std::string& name, const vnx::Variant& value);
	
	friend std::ostream& operator<<(std::ostream& _out, const pooling_error_e& _value);
	friend std::istream& operator>>(std::istream& _in, pooling_error_e& _value);
	
	static const vnx::TypeCode* static_get_type_code();
	static std::shared_ptr<vnx::TypeCode> static_create_type_code();
	
};

template<typename T>
void pooling_error_e::accept_generic(T& _visitor) const {
	_visitor.template type_begin<pooling_error_e>(1);
	_visitor.type_field("value", 0); _visitor.accept(value);
	_visitor.template type_end<pooling_error_e>(1);
}


} // namespace mmx


namespace vnx {

void read(TypeInput& in, ::mmx::pooling_error_e::enum_t& value, const TypeCode* type_code, const uint16_t* code); ///< \private

void write(TypeOutput& out, const ::mmx::pooling_error_e::enum_t& value, const TypeCode* type_code, const uint16_t* code); ///< \private

template<>
std::string to_string(const ::mmx::pooling_error_e& _value); ///< \private

template<>
std::string to_string_value(const ::mmx::pooling_error_e& _value); ///< \private

template<>
std::string to_string_value_full(const ::mmx::pooling_error_e& _value); ///< \private

template<>
std::string to_string(const ::mmx::pooling_error_e::enum_t& _value); ///< \private

template<>
std::string to_string_value(const ::mmx::pooling_error_e::enum_t& _value); ///< \private

template<>
std::string to_string_value_full(const ::mmx::pooling_error_e::enum_t& _value); ///< \private

template<>
struct is_equivalent<::mmx::pooling_error_e> {
	bool operator()(const uint16_t* code, const TypeCode* type_code);
};

} // vnx

#endif // INCLUDE_mmx_pooling_error_e_HXX_