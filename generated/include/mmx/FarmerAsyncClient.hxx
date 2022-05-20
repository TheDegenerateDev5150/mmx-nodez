
// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_mmx_Farmer_ASYNC_CLIENT_HXX_
#define INCLUDE_mmx_Farmer_ASYNC_CLIENT_HXX_

#include <vnx/AsyncClient.h>
#include <mmx/BlockHeader.hxx>
#include <mmx/FarmInfo.hxx>
#include <mmx/ProofOfSpace.hxx>
#include <mmx/addr_t.hpp>
#include <mmx/bls_pubkey_t.hpp>
#include <mmx/bls_signature_t.hpp>
#include <vnx/Hash64.hpp>
#include <vnx/Module.h>
#include <vnx/TopicPtr.hpp>


namespace mmx {

class FarmerAsyncClient : public vnx::AsyncClient {
public:
	FarmerAsyncClient(const std::string& service_name);
	
	FarmerAsyncClient(vnx::Hash64 service_addr);
	
	uint64_t get_mac_addr(
			const std::function<void(const ::vnx::Hash64&)>& _callback = std::function<void(const ::vnx::Hash64&)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t get_farmer_keys(
			const std::function<void(const std::vector<::mmx::bls_pubkey_t>&)>& _callback = std::function<void(const std::vector<::mmx::bls_pubkey_t>&)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t get_farm_info(
			const std::function<void(std::shared_ptr<const ::mmx::FarmInfo>)>& _callback = std::function<void(std::shared_ptr<const ::mmx::FarmInfo>)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t sign_proof(std::shared_ptr<const ::mmx::ProofOfSpace> proof = nullptr, 
			const std::function<void(const ::mmx::bls_signature_t&)>& _callback = std::function<void(const ::mmx::bls_signature_t&)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t sign_block(std::shared_ptr<const ::mmx::BlockHeader> block = nullptr, const uint64_t& reward_amount = 0, 
			const std::function<void(std::shared_ptr<const ::mmx::BlockHeader>)>& _callback = std::function<void(std::shared_ptr<const ::mmx::BlockHeader>)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t vnx_get_config_object(
			const std::function<void(const ::vnx::Object&)>& _callback = std::function<void(const ::vnx::Object&)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t vnx_get_config(const std::string& name = "", 
			const std::function<void(const ::vnx::Variant&)>& _callback = std::function<void(const ::vnx::Variant&)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t vnx_set_config_object(const ::vnx::Object& config = ::vnx::Object(), 
			const std::function<void()>& _callback = std::function<void()>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t vnx_set_config(const std::string& name = "", const ::vnx::Variant& value = ::vnx::Variant(), 
			const std::function<void()>& _callback = std::function<void()>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t vnx_get_type_code(
			const std::function<void(const ::vnx::TypeCode&)>& _callback = std::function<void(const ::vnx::TypeCode&)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t vnx_get_module_info(
			const std::function<void(std::shared_ptr<const ::vnx::ModuleInfo>)>& _callback = std::function<void(std::shared_ptr<const ::vnx::ModuleInfo>)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t vnx_restart(
			const std::function<void()>& _callback = std::function<void()>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t vnx_stop(
			const std::function<void()>& _callback = std::function<void()>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t vnx_self_test(
			const std::function<void(const vnx::bool_t&)>& _callback = std::function<void(const vnx::bool_t&)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
protected:
	int32_t vnx_purge_request(uint64_t _request_id, const vnx::exception& _ex) override;
	
	int32_t vnx_callback_switch(uint64_t _request_id, std::shared_ptr<const vnx::Value> _value) override;
	
private:
	std::unordered_map<uint64_t, std::pair<std::function<void(const ::vnx::Hash64&)>, std::function<void(const vnx::exception&)>>> vnx_queue_get_mac_addr;
	std::unordered_map<uint64_t, std::pair<std::function<void(const std::vector<::mmx::bls_pubkey_t>&)>, std::function<void(const vnx::exception&)>>> vnx_queue_get_farmer_keys;
	std::unordered_map<uint64_t, std::pair<std::function<void(std::shared_ptr<const ::mmx::FarmInfo>)>, std::function<void(const vnx::exception&)>>> vnx_queue_get_farm_info;
	std::unordered_map<uint64_t, std::pair<std::function<void(const ::mmx::bls_signature_t&)>, std::function<void(const vnx::exception&)>>> vnx_queue_sign_proof;
	std::unordered_map<uint64_t, std::pair<std::function<void(std::shared_ptr<const ::mmx::BlockHeader>)>, std::function<void(const vnx::exception&)>>> vnx_queue_sign_block;
	std::unordered_map<uint64_t, std::pair<std::function<void(const ::vnx::Object&)>, std::function<void(const vnx::exception&)>>> vnx_queue_vnx_get_config_object;
	std::unordered_map<uint64_t, std::pair<std::function<void(const ::vnx::Variant&)>, std::function<void(const vnx::exception&)>>> vnx_queue_vnx_get_config;
	std::unordered_map<uint64_t, std::pair<std::function<void()>, std::function<void(const vnx::exception&)>>> vnx_queue_vnx_set_config_object;
	std::unordered_map<uint64_t, std::pair<std::function<void()>, std::function<void(const vnx::exception&)>>> vnx_queue_vnx_set_config;
	std::unordered_map<uint64_t, std::pair<std::function<void(const ::vnx::TypeCode&)>, std::function<void(const vnx::exception&)>>> vnx_queue_vnx_get_type_code;
	std::unordered_map<uint64_t, std::pair<std::function<void(std::shared_ptr<const ::vnx::ModuleInfo>)>, std::function<void(const vnx::exception&)>>> vnx_queue_vnx_get_module_info;
	std::unordered_map<uint64_t, std::pair<std::function<void()>, std::function<void(const vnx::exception&)>>> vnx_queue_vnx_restart;
	std::unordered_map<uint64_t, std::pair<std::function<void()>, std::function<void(const vnx::exception&)>>> vnx_queue_vnx_stop;
	std::unordered_map<uint64_t, std::pair<std::function<void(const vnx::bool_t&)>, std::function<void(const vnx::exception&)>>> vnx_queue_vnx_self_test;
	
};


} // namespace mmx

#endif // INCLUDE_mmx_Farmer_ASYNC_CLIENT_HXX_
