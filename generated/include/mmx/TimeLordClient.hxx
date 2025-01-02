
// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_mmx_TimeLord_CLIENT_HXX_
#define INCLUDE_mmx_TimeLord_CLIENT_HXX_

#include <vnx/Client.h>
#include <mmx/IntervalRequest.hxx>
#include <mmx/addr_t.hpp>
#include <vnx/Module.h>
#include <vnx/TopicPtr.hpp>


namespace mmx {

class TimeLordClient : public vnx::Client {
public:
	TimeLordClient(const std::string& service_name);
	
	TimeLordClient(vnx::Hash64 service_addr);
	
	void stop_vdf();
	
	void stop_vdf_async();
	
	::vnx::Object vnx_get_config_object();
	
	::vnx::Variant vnx_get_config(const std::string& name = "");
	
	void vnx_set_config_object(const ::vnx::Object& config = ::vnx::Object());
	
	void vnx_set_config_object_async(const ::vnx::Object& config = ::vnx::Object());
	
	void vnx_set_config(const std::string& name = "", const ::vnx::Variant& value = ::vnx::Variant());
	
	void vnx_set_config_async(const std::string& name = "", const ::vnx::Variant& value = ::vnx::Variant());
	
	::vnx::TypeCode vnx_get_type_code();
	
	std::shared_ptr<const ::vnx::ModuleInfo> vnx_get_module_info();
	
	void vnx_restart();
	
	void vnx_restart_async();
	
	void vnx_stop();
	
	void vnx_stop_async();
	
	vnx::bool_t vnx_self_test();
	
};


} // namespace mmx

#endif // INCLUDE_mmx_TimeLord_CLIENT_HXX_
