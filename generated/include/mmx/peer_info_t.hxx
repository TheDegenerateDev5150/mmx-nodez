
// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_mmx_peer_info_t_HXX_
#define INCLUDE_mmx_peer_info_t_HXX_

#include <vnx/Type.h>
#include <mmx/package.hxx>
#include <mmx/node_type_e.hxx>


namespace mmx {

struct MMX_EXPORT peer_info_t {
	
	
	uint64_t id = 0;
	std::string address;
	::mmx::node_type_e type;
	uint32_t credits = 0;
	int32_t ping_ms = 0;
	uint32_t height = 0;
	uint32_t version = 0;
	int64_t recv_timeout_ms = 0;
	int64_t connect_time_ms = 0;
	uint64_t bytes_send = 0;
	uint64_t bytes_recv = 0;
	vnx::float64_t pending_cost = 0;
	vnx::bool_t is_synced = 0;
	vnx::bool_t is_paused = 0;
	vnx::bool_t is_blocked = 0;
	vnx::bool_t is_outbound = 0;
	
	static const vnx::Hash64 VNX_TYPE_HASH;
	static const vnx::Hash64 VNX_CODE_HASH;
	
	static constexpr uint64_t VNX_TYPE_ID = 0xce0ff32e89625afbull;
	
	peer_info_t() {}
	
	vnx::Hash64 get_type_hash() const;
	std::string get_type_name() const;
	const vnx::TypeCode* get_type_code() const;
	
	static std::shared_ptr<peer_info_t> create();
	std::shared_ptr<peer_info_t> clone() const;
	
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
	
	friend std::ostream& operator<<(std::ostream& _out, const peer_info_t& _value);
	friend std::istream& operator>>(std::istream& _in, peer_info_t& _value);
	
	static const vnx::TypeCode* static_get_type_code();
	static std::shared_ptr<vnx::TypeCode> static_create_type_code();
	
};

template<typename T>
void peer_info_t::accept_generic(T& _visitor) const {
	_visitor.template type_begin<peer_info_t>(16);
	_visitor.type_field("id", 0); _visitor.accept(id);
	_visitor.type_field("address", 1); _visitor.accept(address);
	_visitor.type_field("type", 2); _visitor.accept(type);
	_visitor.type_field("credits", 3); _visitor.accept(credits);
	_visitor.type_field("ping_ms", 4); _visitor.accept(ping_ms);
	_visitor.type_field("height", 5); _visitor.accept(height);
	_visitor.type_field("version", 6); _visitor.accept(version);
	_visitor.type_field("recv_timeout_ms", 7); _visitor.accept(recv_timeout_ms);
	_visitor.type_field("connect_time_ms", 8); _visitor.accept(connect_time_ms);
	_visitor.type_field("bytes_send", 9); _visitor.accept(bytes_send);
	_visitor.type_field("bytes_recv", 10); _visitor.accept(bytes_recv);
	_visitor.type_field("pending_cost", 11); _visitor.accept(pending_cost);
	_visitor.type_field("is_synced", 12); _visitor.accept(is_synced);
	_visitor.type_field("is_paused", 13); _visitor.accept(is_paused);
	_visitor.type_field("is_blocked", 14); _visitor.accept(is_blocked);
	_visitor.type_field("is_outbound", 15); _visitor.accept(is_outbound);
	_visitor.template type_end<peer_info_t>(16);
}


} // namespace mmx


namespace vnx {

template<>
struct is_equivalent<::mmx::peer_info_t> {
	bool operator()(const uint16_t* code, const TypeCode* type_code);
};

} // vnx

#endif // INCLUDE_mmx_peer_info_t_HXX_
