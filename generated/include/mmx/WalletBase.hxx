
// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_mmx_WalletBase_HXX_
#define INCLUDE_mmx_WalletBase_HXX_

#include <mmx/package.hxx>
#include <mmx/Contract.hxx>
#include <mmx/KeyFile.hxx>
#include <mmx/Solution.hxx>
#include <mmx/Transaction.hxx>
#include <mmx/account_info_t.hxx>
#include <mmx/account_t.hxx>
#include <mmx/addr_t.hpp>
#include <mmx/balance_t.hxx>
#include <mmx/hash_t.hpp>
#include <mmx/offer_data_t.hxx>
#include <mmx/pubkey_t.hpp>
#include <mmx/skey_t.hpp>
#include <mmx/spend_options_t.hxx>
#include <mmx/tx_entry_t.hxx>
#include <mmx/tx_log_entry_t.hxx>
#include <mmx/tx_type_e.hxx>
#include <mmx/txin_t.hxx>
#include <mmx/uint128.hpp>
#include <mmx/virtual_plot_info_t.hxx>
#include <vnx/Module.h>
#include <vnx/Variant.hpp>
#include <vnx/addons/HttpData.hxx>
#include <vnx/addons/HttpRequest.hxx>
#include <vnx/addons/HttpResponse.hxx>


namespace mmx {

class MMX_EXPORT WalletBase : public ::vnx::Module {
public:
	
	std::vector<std::string> key_files;
	std::vector<::mmx::account_t> accounts;
	std::string config_path;
	std::string storage_path;
	std::string database_path = "wallet/";
	std::string node_server = "Node";
	uint32_t max_key_files = 100;
	uint32_t num_addresses = 100;
	uint32_t default_expire = 100;
	int32_t lock_timeout_sec = 600;
	int32_t cache_timeout_ms = 1000;
	vnx::bool_t enable_bls = true;
	std::set<::mmx::addr_t> token_whitelist;
	
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
	
	virtual std::shared_ptr<const ::mmx::Transaction> send(const uint32_t& index, const uint64_t& amount, const ::mmx::addr_t& dst_addr, const ::mmx::addr_t& currency, const ::mmx::spend_options_t& options) const = 0;
	virtual std::shared_ptr<const ::mmx::Transaction> send_many(const uint32_t& index, const std::map<::mmx::addr_t, uint64_t>& amounts, const ::mmx::addr_t& currency, const ::mmx::spend_options_t& options) const = 0;
	virtual std::shared_ptr<const ::mmx::Transaction> send_from(const uint32_t& index, const uint64_t& amount, const ::mmx::addr_t& dst_addr, const ::mmx::addr_t& src_addr, const ::mmx::addr_t& currency, const ::mmx::spend_options_t& options) const = 0;
	virtual std::shared_ptr<const ::mmx::Transaction> deploy(const uint32_t& index, std::shared_ptr<const ::mmx::Contract> contract, const ::mmx::spend_options_t& options) const = 0;
	virtual std::shared_ptr<const ::mmx::Transaction> execute(const uint32_t& index, const ::mmx::addr_t& address, const std::string& method, const std::vector<::vnx::Variant>& args, const vnx::optional<uint32_t>& user, const ::mmx::spend_options_t& options) const = 0;
	virtual std::shared_ptr<const ::mmx::Transaction> deposit(const uint32_t& index, const ::mmx::addr_t& address, const std::string& method, const std::vector<::vnx::Variant>& args, const uint64_t& amount, const ::mmx::addr_t& currency, const ::mmx::spend_options_t& options) const = 0;
	virtual std::shared_ptr<const ::mmx::Transaction> make_offer(const uint32_t& index, const uint32_t& owner, const uint64_t& bid_amount, const ::mmx::addr_t& bid_currency, const uint64_t& ask_amount, const ::mmx::addr_t& ask_currency, const ::mmx::spend_options_t& options) const = 0;
	virtual std::shared_ptr<const ::mmx::Transaction> offer_trade(const uint32_t& index, const ::mmx::addr_t& address, const uint64_t& amount, const uint32_t& dst_addr, const ::mmx::spend_options_t& options) const = 0;
	virtual std::shared_ptr<const ::mmx::Transaction> offer_withdraw(const uint32_t& index, const ::mmx::addr_t& address, const ::mmx::spend_options_t& options) const = 0;
	virtual std::shared_ptr<const ::mmx::Transaction> accept_offer(const uint32_t& index, const ::mmx::addr_t& address, const uint32_t& dst_addr, const ::mmx::spend_options_t& options) const = 0;
	virtual std::shared_ptr<const ::mmx::Transaction> cancel_offer(const uint32_t& index, const ::mmx::addr_t& address, const ::mmx::spend_options_t& options) const = 0;
	virtual std::shared_ptr<const ::mmx::Transaction> swap_trade(const uint32_t& index, const ::mmx::addr_t& address, const uint64_t& amount, const ::mmx::addr_t& currency, const vnx::optional<uint64_t>& min_trade, const int32_t& num_iter, const ::mmx::spend_options_t& options) const = 0;
	virtual std::shared_ptr<const ::mmx::Transaction> swap_add_liquid(const uint32_t& index, const ::mmx::addr_t& address, const std::array<uint64_t, 2>& amount, const uint32_t& pool_idx, const ::mmx::spend_options_t& options) const = 0;
	virtual std::shared_ptr<const ::mmx::Transaction> swap_rem_liquid(const uint32_t& index, const ::mmx::addr_t& address, const std::array<uint64_t, 2>& amount, const ::mmx::spend_options_t& options) const = 0;
	virtual std::shared_ptr<const ::mmx::Transaction> complete(const uint32_t& index, std::shared_ptr<const ::mmx::Transaction> tx, const ::mmx::spend_options_t& options) const = 0;
	virtual std::shared_ptr<const ::mmx::Transaction> sign_off(const uint32_t& index, std::shared_ptr<const ::mmx::Transaction> tx, const ::mmx::spend_options_t& options) const = 0;
	virtual std::shared_ptr<const ::mmx::Solution> sign_msg(const uint32_t& index, const ::mmx::addr_t& address, const ::mmx::hash_t& msg) const = 0;
	virtual void send_off(const uint32_t& index, std::shared_ptr<const ::mmx::Transaction> tx) const = 0;
	virtual void mark_spent(const uint32_t& index, const std::map<std::pair<::mmx::addr_t, ::mmx::addr_t>, ::mmx::uint128>& amounts) = 0;
	virtual void reserve(const uint32_t& index, const std::map<std::pair<::mmx::addr_t, ::mmx::addr_t>, ::mmx::uint128>& amounts) = 0;
	virtual void release(const uint32_t& index, const std::map<std::pair<::mmx::addr_t, ::mmx::addr_t>, ::mmx::uint128>& amounts) = 0;
	virtual void release_all() = 0;
	virtual void reset_cache(const uint32_t& index) = 0;
	virtual void update_cache(const uint32_t& index) const = 0;
	virtual std::vector<::mmx::tx_entry_t> get_history(const uint32_t& index, const uint32_t& since, const uint32_t& until, const int32_t& limit, const vnx::optional<::mmx::tx_type_e>& type, const vnx::optional<::mmx::addr_t>& currency) const = 0;
	virtual std::vector<::mmx::tx_entry_t> get_history_memo(const uint32_t& index, const std::string& memo, const int32_t& limit, const vnx::optional<::mmx::addr_t>& currency) const = 0;
	virtual std::vector<::mmx::tx_log_entry_t> get_tx_log(const uint32_t& index, const int32_t& limit, const uint32_t& offset) const = 0;
	virtual std::vector<::mmx::txin_t> gather_inputs_for(const uint32_t& index, const uint64_t& amount, const ::mmx::addr_t& currency, const ::mmx::spend_options_t& options) const = 0;
	virtual ::mmx::balance_t get_balance(const uint32_t& index, const ::mmx::addr_t& currency) const = 0;
	virtual std::map<::mmx::addr_t, ::mmx::balance_t> get_balances(const uint32_t& index, const vnx::bool_t& with_zero, const vnx::bool_t& show_all) const = 0;
	virtual std::map<::mmx::addr_t, ::mmx::balance_t> get_total_balances(const std::vector<::mmx::addr_t>& addresses) const = 0;
	virtual std::map<::mmx::addr_t, ::mmx::balance_t> get_contract_balances(const ::mmx::addr_t& address) const = 0;
	virtual std::map<::mmx::addr_t, std::shared_ptr<const ::mmx::Contract>> get_contracts(const uint32_t& index, const vnx::optional<std::string>& type_name) const = 0;
	virtual std::map<::mmx::addr_t, std::shared_ptr<const ::mmx::Contract>> get_contracts_owned(const uint32_t& index, const vnx::optional<std::string>& type_name) const = 0;
	virtual std::vector<::mmx::virtual_plot_info_t> get_virtual_plots(const uint32_t& index) const = 0;
	virtual std::vector<::mmx::offer_data_t> get_offers(const uint32_t& index, const vnx::bool_t& state) const = 0;
	virtual std::map<::mmx::addr_t, std::array<std::pair<::mmx::addr_t, ::mmx::uint128>, 2>> get_swap_liquidity(const uint32_t& index) const = 0;
	virtual ::mmx::addr_t get_address(const uint32_t& index, const uint32_t& offset) const = 0;
	virtual std::vector<::mmx::addr_t> get_all_addresses(const int32_t& index) const = 0;
	virtual ::mmx::account_info_t get_account(const uint32_t& index) const = 0;
	virtual std::vector<::mmx::account_info_t> get_all_accounts() const = 0;
	virtual vnx::bool_t is_locked(const uint32_t& index) const = 0;
	virtual void lock(const uint32_t& index) = 0;
	virtual void unlock(const uint32_t& index, const std::string& passphrase) = 0;
	virtual void add_account(const uint32_t& index, const ::mmx::account_t& config, const vnx::optional<std::string>& passphrase) = 0;
	virtual void create_account(const ::mmx::account_t& config, const vnx::optional<std::string>& passphrase) = 0;
	virtual void create_wallet(const ::mmx::account_t& config, const vnx::optional<std::string>& words, const vnx::optional<std::string>& passphrase) = 0;
	virtual void import_wallet(const ::mmx::account_t& config, std::shared_ptr<const ::mmx::KeyFile> key_file, const vnx::optional<std::string>& passphrase) = 0;
	virtual void remove_account(const uint32_t& index, const uint32_t& account) = 0;
	virtual std::shared_ptr<const ::mmx::KeyFile> export_wallet(const uint32_t& index) const = 0;
	virtual std::vector<std::string> get_mnemonic_wordlist(const std::string& lang) const = 0;
	virtual std::set<::mmx::addr_t> get_token_list() const = 0;
	virtual void add_token(const ::mmx::addr_t& address) = 0;
	virtual void rem_token(const ::mmx::addr_t& address) = 0;
	virtual ::mmx::hash_t get_master_seed(const uint32_t& index) const = 0;
	virtual std::vector<std::string> get_mnemonic_seed(const uint32_t& index) const = 0;
	virtual std::pair<::mmx::skey_t, ::mmx::pubkey_t> get_farmer_keys(const uint32_t& index) const = 0;
	virtual std::vector<std::pair<::mmx::skey_t, ::mmx::pubkey_t>> get_all_farmer_keys() const = 0;
	virtual void http_request_async(std::shared_ptr<const ::vnx::addons::HttpRequest> request, const std::string& sub_path, const vnx::request_id_t& _request_id) const = 0;
	void http_request_async_return(const vnx::request_id_t& _request_id, const std::shared_ptr<const ::vnx::addons::HttpResponse>& _ret_0) const;
	virtual void http_request_chunk_async(std::shared_ptr<const ::vnx::addons::HttpRequest> request, const std::string& sub_path, const int64_t& offset, const int64_t& max_bytes, const vnx::request_id_t& _request_id) const = 0;
	void http_request_chunk_async_return(const vnx::request_id_t& _request_id, const std::shared_ptr<const ::vnx::addons::HttpData>& _ret_0) const;
	
	void vnx_handle_switch(std::shared_ptr<const vnx::Value> _value) override;
	std::shared_ptr<vnx::Value> vnx_call_switch(std::shared_ptr<const vnx::Value> _method, const vnx::request_id_t& _request_id) override;
	
};

template<typename T>
void WalletBase::accept_generic(T& _visitor) const {
	_visitor.template type_begin<WalletBase>(13);
	_visitor.type_field("key_files", 0); _visitor.accept(key_files);
	_visitor.type_field("accounts", 1); _visitor.accept(accounts);
	_visitor.type_field("config_path", 2); _visitor.accept(config_path);
	_visitor.type_field("storage_path", 3); _visitor.accept(storage_path);
	_visitor.type_field("database_path", 4); _visitor.accept(database_path);
	_visitor.type_field("node_server", 5); _visitor.accept(node_server);
	_visitor.type_field("max_key_files", 6); _visitor.accept(max_key_files);
	_visitor.type_field("num_addresses", 7); _visitor.accept(num_addresses);
	_visitor.type_field("default_expire", 8); _visitor.accept(default_expire);
	_visitor.type_field("lock_timeout_sec", 9); _visitor.accept(lock_timeout_sec);
	_visitor.type_field("cache_timeout_ms", 10); _visitor.accept(cache_timeout_ms);
	_visitor.type_field("enable_bls", 11); _visitor.accept(enable_bls);
	_visitor.type_field("token_whitelist", 12); _visitor.accept(token_whitelist);
	_visitor.template type_end<WalletBase>(13);
}


} // namespace mmx


namespace vnx {

} // vnx

#endif // INCLUDE_mmx_WalletBase_HXX_
