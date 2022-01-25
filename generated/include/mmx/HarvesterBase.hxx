
// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_mmx_HarvesterBase_HXX_
#define INCLUDE_mmx_HarvesterBase_HXX_

#include <mmx/package.hxx>
#include <mmx/Challenge.hxx>
#include <mmx/FarmInfo.hxx>
#include <vnx/Module.h>
#include <vnx/TopicPtr.hpp>


namespace mmx {

class HarvesterBase : public ::vnx::Module {
public:
	
	::vnx::TopicPtr input_challenges = "harvester.challenges";
	::vnx::TopicPtr output_info = "harvester.info";
	::vnx::TopicPtr output_proofs = "harvester.proof";
	std::vector<std::string> plot_dirs;
	std::string farmer_server = "Farmer";
	int32_t max_queue_ms = 10000;
	int32_t reload_interval = 3600;
	uint32_t num_threads = 0;
	vnx::bool_t recursive_search = true;
	
	typedef ::vnx::Module Super;
	
	static const vnx::Hash64 VNX_TYPE_HASH;
	static const vnx::Hash64 VNX_CODE_HASH;
	
	static constexpr uint64_t VNX_TYPE_ID = 0xc17118896cde1555ull;
	
	HarvesterBase(const std::string& _vnx_name);
	
	vnx::Hash64 get_type_hash() const override;
	std::string get_type_name() const override;
	const vnx::TypeCode* get_type_code() const override;
	
	void read(std::istream& _in) override;
	void write(std::ostream& _out) const override;
	
	template<typename T>
	void accept_generic(T& _visitor) const;
	void accept(vnx::Visitor& _visitor) const override;
	
	vnx::Object to_object() const override;
	void from_object(const vnx::Object& object) override;
	
	vnx::Variant get_field(const std::string& name) const override;
	void set_field(const std::string& name, const vnx::Variant& value) override;
	
	friend std::ostream& operator<<(std::ostream& _out, const HarvesterBase& _value);
	friend std::istream& operator>>(std::istream& _in, HarvesterBase& _value);
	
	static const vnx::TypeCode* static_get_type_code();
	static std::shared_ptr<vnx::TypeCode> static_create_type_code();
	
protected:
	using Super::handle;
	
	virtual void reload() = 0;
	virtual std::shared_ptr<const ::mmx::FarmInfo> get_farm_info() const = 0;
	virtual uint64_t get_total_bytes() const = 0;
	virtual void handle(std::shared_ptr<const ::mmx::Challenge> _value) {}
	
	void vnx_handle_switch(std::shared_ptr<const vnx::Value> _value) override;
	std::shared_ptr<vnx::Value> vnx_call_switch(std::shared_ptr<const vnx::Value> _method, const vnx::request_id_t& _request_id) override;
	
};

template<typename T>
void HarvesterBase::accept_generic(T& _visitor) const {
	_visitor.template type_begin<HarvesterBase>(9);
	_visitor.type_field("input_challenges", 0); _visitor.accept(input_challenges);
	_visitor.type_field("output_info", 1); _visitor.accept(output_info);
	_visitor.type_field("output_proofs", 2); _visitor.accept(output_proofs);
	_visitor.type_field("plot_dirs", 3); _visitor.accept(plot_dirs);
	_visitor.type_field("farmer_server", 4); _visitor.accept(farmer_server);
	_visitor.type_field("max_queue_ms", 5); _visitor.accept(max_queue_ms);
	_visitor.type_field("reload_interval", 6); _visitor.accept(reload_interval);
	_visitor.type_field("num_threads", 7); _visitor.accept(num_threads);
	_visitor.type_field("recursive_search", 8); _visitor.accept(recursive_search);
	_visitor.template type_end<HarvesterBase>(9);
}


} // namespace mmx


namespace vnx {

} // vnx

#endif // INCLUDE_mmx_HarvesterBase_HXX_
