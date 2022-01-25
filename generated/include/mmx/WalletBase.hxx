
// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_mmx_WalletBase_HXX_
#define INCLUDE_mmx_WalletBase_HXX_

#include <mmx/package.hxx>
#include <mmx/Contract.hxx>
#include <mmx/FarmerKeys.hxx>
#include <mmx/Transaction.hxx>
#include <mmx/addr_t.hpp>
#include <mmx/hash_t.hpp>
#include <mmx/spend_options_t.hxx>
#include <mmx/stxo_entry_t.hxx>
#include <mmx/tx_entry_t.hxx>
#include <mmx/txio_key_t.hxx>
#include <mmx/utxo_entry_t.hxx>
#include <vnx/Module.h>
#include <vnx/addons/HttpData.hxx>
#include <vnx/addons/HttpRequest.hxx>
#include <vnx/addons/HttpResponse.hxx>


namespace mmx {

class WalletBase : public ::vnx::Module {
public:
	
	std::vector<std::string> key_files;
	std::string storage_path;
	std::string node_server = "Node";
	uint32_t num_addresses = 100;
	int32_t utxo_timeout_ms = 1000;
	vnx::bool_t enable_bls = true;
	
	typedef ::vnx::Module Super;
	
	static const vnx::Hash64 VNX_TYPE_HASH;
	static const vnx::Hash64 VNX_CODE_HASH;
	
	static constexpr uint64_t VNX_TYPE_ID = 0x62207fd96d3aead7ull;
	
	WalletBase(const std::string& _vnx_name);
	
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
	
	friend std::ostream& operator<<(std::ostream& _out, const WalletBase& _value);
	friend std::istream& operator>>(std::istream& _in, WalletBase& _value);
	
	static const vnx::TypeCode* static_get_type_code();
	static std::shared_ptr<vnx::TypeCode> static_create_type_code();
	
protected:
	using Super::handle;
	
	virtual ::mmx::hash_t send(const uint32_t& index, const uint64_t& amount, const ::mmx::addr_t& dst_addr, const ::mmx::addr_t& currency, const ::mmx::spend_options_t& options) const = 0;
	virtual ::mmx::hash_t send_from(const uint32_t& index, const uint64_t& amount, const ::mmx::addr_t& dst_addr, const ::mmx::addr_t& src_addr, const ::mmx::addr_t& currency, const ::mmx::spend_options_t& options) const = 0;
	virtual ::mmx::hash_t mint(const uint32_t& index, const uint64_t& amount, const ::mmx::addr_t& dst_addr, const ::mmx::addr_t& currency, const ::mmx::spend_options_t& options) const = 0;
	virtual ::mmx::hash_t deploy(const uint32_t& index, std::shared_ptr<const ::mmx::Contract> contract, const ::mmx::spend_options_t& options) const = 0;
	virtual std::shared_ptr<const ::mmx::Transaction> sign_off(const uint32_t& index, std::shared_ptr<const ::mmx::Transaction> tx) const = 0;
	virtual void reserve(const uint32_t& index, const std::vector<::mmx::txio_key_t>& keys) = 0;
	virtual void release(const uint32_t& index, const std::vector<::mmx::txio_key_t>& keys) = 0;
	virtual void release_all() = 0;
	virtual std::vector<::mmx::utxo_entry_t> get_utxo_list(const uint32_t& index, const uint32_t& min_confirm) const = 0;
	virtual std::vector<::mmx::utxo_entry_t> get_utxo_list_for(const uint32_t& index, const ::mmx::addr_t& currency, const uint32_t& min_confirm) const = 0;
	virtual std::vector<::mmx::stxo_entry_t> get_stxo_list(const uint32_t& index) const = 0;
	virtual std::vector<::mmx::stxo_entry_t> get_stxo_list_for(const uint32_t& index, const ::mmx::addr_t& currency) const = 0;
	virtual std::vector<::mmx::utxo_entry_t> gather_utxos_for(const uint32_t& index, const uint64_t& amount, const ::mmx::addr_t& currency, const ::mmx::spend_options_t& options) const = 0;
	virtual std::vector<::mmx::tx_entry_t> get_history(const uint32_t& index, const int32_t& since) const = 0;
	virtual uint64_t get_balance(const uint32_t& index, const ::mmx::addr_t& currency, const uint32_t& min_confirm) const = 0;
	virtual std::map<::mmx::addr_t, uint64_t> get_balances(const uint32_t& index, const uint32_t& min_confirm) const = 0;
	virtual std::map<::mmx::addr_t, std::shared_ptr<const ::mmx::Contract>> get_contracts(const uint32_t& index) const = 0;
	virtual ::mmx::addr_t get_address(const uint32_t& index, const uint32_t& offset) const = 0;
	virtual std::vector<::mmx::addr_t> get_all_addresses(const int32_t& index) const = 0;
	virtual ::mmx::hash_t get_master_seed(const uint32_t& index) const = 0;
	virtual std::shared_ptr<const ::mmx::FarmerKeys> get_farmer_keys(const uint32_t& index) const = 0;
	virtual std::vector<std::shared_ptr<const ::mmx::FarmerKeys>> get_all_farmer_keys() const = 0;
	virtual void http_request_async(std::shared_ptr<const ::vnx::addons::HttpRequest> request, const std::string& sub_path, const vnx::request_id_t& _request_id) const = 0;
	void http_request_async_return(const vnx::request_id_t& _request_id, const std::shared_ptr<const ::vnx::addons::HttpResponse>& _ret_0) const;
	virtual void http_request_chunk_async(std::shared_ptr<const ::vnx::addons::HttpRequest> request, const std::string& sub_path, const int64_t& offset, const int64_t& max_bytes, const vnx::request_id_t& _request_id) const = 0;
	void http_request_chunk_async_return(const vnx::request_id_t& _request_id, const std::shared_ptr<const ::vnx::addons::HttpData>& _ret_0) const;
	
	void vnx_handle_switch(std::shared_ptr<const vnx::Value> _value) override;
	std::shared_ptr<vnx::Value> vnx_call_switch(std::shared_ptr<const vnx::Value> _method, const vnx::request_id_t& _request_id) override;
	
};

template<typename T>
void WalletBase::accept_generic(T& _visitor) const {
	_visitor.template type_begin<WalletBase>(6);
	_visitor.type_field("key_files", 0); _visitor.accept(key_files);
	_visitor.type_field("storage_path", 1); _visitor.accept(storage_path);
	_visitor.type_field("node_server", 2); _visitor.accept(node_server);
	_visitor.type_field("num_addresses", 3); _visitor.accept(num_addresses);
	_visitor.type_field("utxo_timeout_ms", 4); _visitor.accept(utxo_timeout_ms);
	_visitor.type_field("enable_bls", 5); _visitor.accept(enable_bls);
	_visitor.template type_end<WalletBase>(6);
}


} // namespace mmx


namespace vnx {

} // vnx

#endif // INCLUDE_mmx_WalletBase_HXX_
