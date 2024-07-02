
// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_mmx_Wallet_ASYNC_CLIENT_HXX_
#define INCLUDE_mmx_Wallet_ASYNC_CLIENT_HXX_

#include <vnx/AsyncClient.h>
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

class WalletAsyncClient : public vnx::AsyncClient {
public:
	WalletAsyncClient(const std::string& service_name);
	
	WalletAsyncClient(vnx::Hash64 service_addr);
	
	uint64_t send(const uint32_t& index = 0, const uint64_t& amount = 0, const ::mmx::addr_t& dst_addr = ::mmx::addr_t(), const ::mmx::addr_t& currency = ::mmx::addr_t(), const ::mmx::spend_options_t& options = ::mmx::spend_options_t(), 
			const std::function<void(std::shared_ptr<const ::mmx::Transaction>)>& _callback = std::function<void(std::shared_ptr<const ::mmx::Transaction>)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t send_many(const uint32_t& index = 0, const std::map<::mmx::addr_t, uint64_t>& amounts = {}, const ::mmx::addr_t& currency = ::mmx::addr_t(), const ::mmx::spend_options_t& options = ::mmx::spend_options_t(), 
			const std::function<void(std::shared_ptr<const ::mmx::Transaction>)>& _callback = std::function<void(std::shared_ptr<const ::mmx::Transaction>)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t send_from(const uint32_t& index = 0, const uint64_t& amount = 0, const ::mmx::addr_t& dst_addr = ::mmx::addr_t(), const ::mmx::addr_t& src_addr = ::mmx::addr_t(), const ::mmx::addr_t& currency = ::mmx::addr_t(), const ::mmx::spend_options_t& options = ::mmx::spend_options_t(), 
			const std::function<void(std::shared_ptr<const ::mmx::Transaction>)>& _callback = std::function<void(std::shared_ptr<const ::mmx::Transaction>)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t deploy(const uint32_t& index = 0, std::shared_ptr<const ::mmx::Contract> contract = nullptr, const ::mmx::spend_options_t& options = ::mmx::spend_options_t(), 
			const std::function<void(std::shared_ptr<const ::mmx::Transaction>)>& _callback = std::function<void(std::shared_ptr<const ::mmx::Transaction>)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t execute(const uint32_t& index = 0, const ::mmx::addr_t& address = ::mmx::addr_t(), const std::string& method = "", const std::vector<::vnx::Variant>& args = {}, const vnx::optional<uint32_t>& user = nullptr, const ::mmx::spend_options_t& options = ::mmx::spend_options_t(), 
			const std::function<void(std::shared_ptr<const ::mmx::Transaction>)>& _callback = std::function<void(std::shared_ptr<const ::mmx::Transaction>)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t deposit(const uint32_t& index = 0, const ::mmx::addr_t& address = ::mmx::addr_t(), const std::string& method = "", const std::vector<::vnx::Variant>& args = {}, const uint64_t& amount = 0, const ::mmx::addr_t& currency = ::mmx::addr_t(), const ::mmx::spend_options_t& options = ::mmx::spend_options_t(), 
			const std::function<void(std::shared_ptr<const ::mmx::Transaction>)>& _callback = std::function<void(std::shared_ptr<const ::mmx::Transaction>)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t make_offer(const uint32_t& index = 0, const uint32_t& owner = 0, const uint64_t& bid_amount = 0, const ::mmx::addr_t& bid_currency = ::mmx::addr_t(), const uint64_t& ask_amount = 0, const ::mmx::addr_t& ask_currency = ::mmx::addr_t(), const ::mmx::spend_options_t& options = ::mmx::spend_options_t(), 
			const std::function<void(std::shared_ptr<const ::mmx::Transaction>)>& _callback = std::function<void(std::shared_ptr<const ::mmx::Transaction>)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t offer_trade(const uint32_t& index = 0, const ::mmx::addr_t& address = ::mmx::addr_t(), const uint64_t& amount = 0, const uint32_t& dst_addr = 0, const ::mmx::spend_options_t& options = ::mmx::spend_options_t(), 
			const std::function<void(std::shared_ptr<const ::mmx::Transaction>)>& _callback = std::function<void(std::shared_ptr<const ::mmx::Transaction>)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t offer_withdraw(const uint32_t& index = 0, const ::mmx::addr_t& address = ::mmx::addr_t(), const ::mmx::spend_options_t& options = ::mmx::spend_options_t(), 
			const std::function<void(std::shared_ptr<const ::mmx::Transaction>)>& _callback = std::function<void(std::shared_ptr<const ::mmx::Transaction>)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t accept_offer(const uint32_t& index = 0, const ::mmx::addr_t& address = ::mmx::addr_t(), const uint32_t& dst_addr = 0, const ::mmx::spend_options_t& options = ::mmx::spend_options_t(), 
			const std::function<void(std::shared_ptr<const ::mmx::Transaction>)>& _callback = std::function<void(std::shared_ptr<const ::mmx::Transaction>)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t cancel_offer(const uint32_t& index = 0, const ::mmx::addr_t& address = ::mmx::addr_t(), const ::mmx::spend_options_t& options = ::mmx::spend_options_t(), 
			const std::function<void(std::shared_ptr<const ::mmx::Transaction>)>& _callback = std::function<void(std::shared_ptr<const ::mmx::Transaction>)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t swap_trade(const uint32_t& index = 0, const ::mmx::addr_t& address = ::mmx::addr_t(), const uint64_t& amount = 0, const ::mmx::addr_t& currency = ::mmx::addr_t(), const vnx::optional<uint64_t>& min_trade = nullptr, const int32_t& num_iter = 20, const ::mmx::spend_options_t& options = ::mmx::spend_options_t(), 
			const std::function<void(std::shared_ptr<const ::mmx::Transaction>)>& _callback = std::function<void(std::shared_ptr<const ::mmx::Transaction>)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t swap_add_liquid(const uint32_t& index = 0, const ::mmx::addr_t& address = ::mmx::addr_t(), const std::array<uint64_t, 2>& amount = {}, const uint32_t& pool_idx = 0, const ::mmx::spend_options_t& options = ::mmx::spend_options_t(), 
			const std::function<void(std::shared_ptr<const ::mmx::Transaction>)>& _callback = std::function<void(std::shared_ptr<const ::mmx::Transaction>)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t swap_rem_liquid(const uint32_t& index = 0, const ::mmx::addr_t& address = ::mmx::addr_t(), const std::array<uint64_t, 2>& amount = {}, const ::mmx::spend_options_t& options = ::mmx::spend_options_t(), 
			const std::function<void(std::shared_ptr<const ::mmx::Transaction>)>& _callback = std::function<void(std::shared_ptr<const ::mmx::Transaction>)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t complete(const uint32_t& index = 0, std::shared_ptr<const ::mmx::Transaction> tx = nullptr, const ::mmx::spend_options_t& options = ::mmx::spend_options_t(), 
			const std::function<void(std::shared_ptr<const ::mmx::Transaction>)>& _callback = std::function<void(std::shared_ptr<const ::mmx::Transaction>)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t sign_off(const uint32_t& index = 0, std::shared_ptr<const ::mmx::Transaction> tx = nullptr, const ::mmx::spend_options_t& options = ::mmx::spend_options_t(), 
			const std::function<void(std::shared_ptr<const ::mmx::Transaction>)>& _callback = std::function<void(std::shared_ptr<const ::mmx::Transaction>)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t sign_msg(const uint32_t& index = 0, const ::mmx::addr_t& address = ::mmx::addr_t(), const ::mmx::hash_t& msg = ::mmx::hash_t(), 
			const std::function<void(std::shared_ptr<const ::mmx::Solution>)>& _callback = std::function<void(std::shared_ptr<const ::mmx::Solution>)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t send_off(const uint32_t& index = 0, std::shared_ptr<const ::mmx::Transaction> tx = nullptr, 
			const std::function<void()>& _callback = std::function<void()>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t mark_spent(const uint32_t& index = 0, const std::map<std::pair<::mmx::addr_t, ::mmx::addr_t>, ::mmx::uint128>& amounts = {}, 
			const std::function<void()>& _callback = std::function<void()>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t reserve(const uint32_t& index = 0, const std::map<std::pair<::mmx::addr_t, ::mmx::addr_t>, ::mmx::uint128>& amounts = {}, 
			const std::function<void()>& _callback = std::function<void()>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t release(const uint32_t& index = 0, const std::map<std::pair<::mmx::addr_t, ::mmx::addr_t>, ::mmx::uint128>& amounts = {}, 
			const std::function<void()>& _callback = std::function<void()>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t release_all(
			const std::function<void()>& _callback = std::function<void()>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t reset_cache(const uint32_t& index = 0, 
			const std::function<void()>& _callback = std::function<void()>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t update_cache(const uint32_t& index = 0, 
			const std::function<void()>& _callback = std::function<void()>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t get_history(const uint32_t& index = 0, const uint32_t& since = 0, const uint32_t& until = -1, const int32_t& limit = -1, const vnx::optional<::mmx::tx_type_e>& type = nullptr, const vnx::optional<::mmx::addr_t>& currency = nullptr, 
			const std::function<void(const std::vector<::mmx::tx_entry_t>&)>& _callback = std::function<void(const std::vector<::mmx::tx_entry_t>&)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t get_history_memo(const uint32_t& index = 0, const std::string& memo = "", const int32_t& limit = -1, const vnx::optional<::mmx::addr_t>& currency = nullptr, 
			const std::function<void(const std::vector<::mmx::tx_entry_t>&)>& _callback = std::function<void(const std::vector<::mmx::tx_entry_t>&)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t get_tx_log(const uint32_t& index = 0, const int32_t& limit = -1, const uint32_t& offset = 0, 
			const std::function<void(const std::vector<::mmx::tx_log_entry_t>&)>& _callback = std::function<void(const std::vector<::mmx::tx_log_entry_t>&)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t gather_inputs_for(const uint32_t& index = 0, const uint64_t& amount = 0, const ::mmx::addr_t& currency = ::mmx::addr_t(), const ::mmx::spend_options_t& options = ::mmx::spend_options_t(), 
			const std::function<void(const std::vector<::mmx::txin_t>&)>& _callback = std::function<void(const std::vector<::mmx::txin_t>&)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t get_balance(const uint32_t& index = 0, const ::mmx::addr_t& currency = ::mmx::addr_t(), 
			const std::function<void(const ::mmx::balance_t&)>& _callback = std::function<void(const ::mmx::balance_t&)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t get_balances(const uint32_t& index = 0, const vnx::bool_t& with_zero = 0, const vnx::bool_t& show_all = 0, 
			const std::function<void(const std::map<::mmx::addr_t, ::mmx::balance_t>&)>& _callback = std::function<void(const std::map<::mmx::addr_t, ::mmx::balance_t>&)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t get_total_balances(const std::vector<::mmx::addr_t>& addresses = {}, 
			const std::function<void(const std::map<::mmx::addr_t, ::mmx::balance_t>&)>& _callback = std::function<void(const std::map<::mmx::addr_t, ::mmx::balance_t>&)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t get_contract_balances(const ::mmx::addr_t& address = ::mmx::addr_t(), 
			const std::function<void(const std::map<::mmx::addr_t, ::mmx::balance_t>&)>& _callback = std::function<void(const std::map<::mmx::addr_t, ::mmx::balance_t>&)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t get_contracts(const uint32_t& index = 0, const vnx::optional<std::string>& type_name = nullptr, 
			const std::function<void(const std::map<::mmx::addr_t, std::shared_ptr<const ::mmx::Contract>>&)>& _callback = std::function<void(const std::map<::mmx::addr_t, std::shared_ptr<const ::mmx::Contract>>&)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t get_contracts_owned(const uint32_t& index = 0, const vnx::optional<std::string>& type_name = nullptr, 
			const std::function<void(const std::map<::mmx::addr_t, std::shared_ptr<const ::mmx::Contract>>&)>& _callback = std::function<void(const std::map<::mmx::addr_t, std::shared_ptr<const ::mmx::Contract>>&)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t get_virtual_plots(const uint32_t& index = 0, 
			const std::function<void(const std::vector<::mmx::virtual_plot_info_t>&)>& _callback = std::function<void(const std::vector<::mmx::virtual_plot_info_t>&)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t get_offers(const uint32_t& index = 0, const vnx::bool_t& state = 0, 
			const std::function<void(const std::vector<::mmx::offer_data_t>&)>& _callback = std::function<void(const std::vector<::mmx::offer_data_t>&)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t get_swap_liquidity(const uint32_t& index = 0, 
			const std::function<void(const std::map<::mmx::addr_t, std::array<std::pair<::mmx::addr_t, ::mmx::uint128>, 2>>&)>& _callback = std::function<void(const std::map<::mmx::addr_t, std::array<std::pair<::mmx::addr_t, ::mmx::uint128>, 2>>&)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t get_address(const uint32_t& index = 0, const uint32_t& offset = 0, 
			const std::function<void(const ::mmx::addr_t&)>& _callback = std::function<void(const ::mmx::addr_t&)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t get_all_addresses(const int32_t& index = 0, 
			const std::function<void(const std::vector<::mmx::addr_t>&)>& _callback = std::function<void(const std::vector<::mmx::addr_t>&)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t get_account(const uint32_t& index = 0, 
			const std::function<void(const ::mmx::account_info_t&)>& _callback = std::function<void(const ::mmx::account_info_t&)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t get_all_accounts(
			const std::function<void(const std::vector<::mmx::account_info_t>&)>& _callback = std::function<void(const std::vector<::mmx::account_info_t>&)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t is_locked(const uint32_t& index = 0, 
			const std::function<void(const vnx::bool_t&)>& _callback = std::function<void(const vnx::bool_t&)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t lock(const uint32_t& index = 0, 
			const std::function<void()>& _callback = std::function<void()>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t unlock(const uint32_t& index = 0, const std::string& passphrase = "", 
			const std::function<void()>& _callback = std::function<void()>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t add_account(const uint32_t& index = 0, const ::mmx::account_t& config = ::mmx::account_t(), const vnx::optional<std::string>& passphrase = nullptr, 
			const std::function<void()>& _callback = std::function<void()>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t create_account(const ::mmx::account_t& config = ::mmx::account_t(), const vnx::optional<std::string>& passphrase = nullptr, 
			const std::function<void()>& _callback = std::function<void()>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t create_wallet(const ::mmx::account_t& config = ::mmx::account_t(), const vnx::optional<std::string>& words = nullptr, const vnx::optional<std::string>& passphrase = nullptr, 
			const std::function<void()>& _callback = std::function<void()>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t import_wallet(const ::mmx::account_t& config = ::mmx::account_t(), std::shared_ptr<const ::mmx::KeyFile> key_file = nullptr, const vnx::optional<std::string>& passphrase = nullptr, 
			const std::function<void()>& _callback = std::function<void()>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t remove_account(const uint32_t& index = 0, const uint32_t& account = 0, 
			const std::function<void()>& _callback = std::function<void()>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t export_wallet(const uint32_t& index = 0, 
			const std::function<void(std::shared_ptr<const ::mmx::KeyFile>)>& _callback = std::function<void(std::shared_ptr<const ::mmx::KeyFile>)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t get_mnemonic_wordlist(const std::string& lang = "en", 
			const std::function<void(const std::vector<std::string>&)>& _callback = std::function<void(const std::vector<std::string>&)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t get_token_list(
			const std::function<void(const std::set<::mmx::addr_t>&)>& _callback = std::function<void(const std::set<::mmx::addr_t>&)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t add_token(const ::mmx::addr_t& address = ::mmx::addr_t(), 
			const std::function<void()>& _callback = std::function<void()>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t rem_token(const ::mmx::addr_t& address = ::mmx::addr_t(), 
			const std::function<void()>& _callback = std::function<void()>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t get_master_seed(const uint32_t& index = 0, 
			const std::function<void(const ::mmx::hash_t&)>& _callback = std::function<void(const ::mmx::hash_t&)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t get_mnemonic_seed(const uint32_t& index = 0, 
			const std::function<void(const std::vector<std::string>&)>& _callback = std::function<void(const std::vector<std::string>&)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t get_farmer_keys(const uint32_t& index = 0, 
			const std::function<void(const std::pair<::mmx::skey_t, ::mmx::pubkey_t>&)>& _callback = std::function<void(const std::pair<::mmx::skey_t, ::mmx::pubkey_t>&)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t get_all_farmer_keys(
			const std::function<void(const std::vector<std::pair<::mmx::skey_t, ::mmx::pubkey_t>>&)>& _callback = std::function<void(const std::vector<std::pair<::mmx::skey_t, ::mmx::pubkey_t>>&)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t http_request(std::shared_ptr<const ::vnx::addons::HttpRequest> request = nullptr, const std::string& sub_path = "", 
			const std::function<void(std::shared_ptr<const ::vnx::addons::HttpResponse>)>& _callback = std::function<void(std::shared_ptr<const ::vnx::addons::HttpResponse>)>(),
			const std::function<void(const vnx::exception&)>& _error_callback = std::function<void(const vnx::exception&)>());
	
	uint64_t http_request_chunk(std::shared_ptr<const ::vnx::addons::HttpRequest> request = nullptr, const std::string& sub_path = "", const int64_t& offset = 0, const int64_t& max_bytes = 0, 
			const std::function<void(std::shared_ptr<const ::vnx::addons::HttpData>)>& _callback = std::function<void(std::shared_ptr<const ::vnx::addons::HttpData>)>(),
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
	std::unordered_map<uint64_t, std::pair<std::function<void(std::shared_ptr<const ::mmx::Transaction>)>, std::function<void(const vnx::exception&)>>> vnx_queue_send;
	std::unordered_map<uint64_t, std::pair<std::function<void(std::shared_ptr<const ::mmx::Transaction>)>, std::function<void(const vnx::exception&)>>> vnx_queue_send_many;
	std::unordered_map<uint64_t, std::pair<std::function<void(std::shared_ptr<const ::mmx::Transaction>)>, std::function<void(const vnx::exception&)>>> vnx_queue_send_from;
	std::unordered_map<uint64_t, std::pair<std::function<void(std::shared_ptr<const ::mmx::Transaction>)>, std::function<void(const vnx::exception&)>>> vnx_queue_deploy;
	std::unordered_map<uint64_t, std::pair<std::function<void(std::shared_ptr<const ::mmx::Transaction>)>, std::function<void(const vnx::exception&)>>> vnx_queue_execute;
	std::unordered_map<uint64_t, std::pair<std::function<void(std::shared_ptr<const ::mmx::Transaction>)>, std::function<void(const vnx::exception&)>>> vnx_queue_deposit;
	std::unordered_map<uint64_t, std::pair<std::function<void(std::shared_ptr<const ::mmx::Transaction>)>, std::function<void(const vnx::exception&)>>> vnx_queue_make_offer;
	std::unordered_map<uint64_t, std::pair<std::function<void(std::shared_ptr<const ::mmx::Transaction>)>, std::function<void(const vnx::exception&)>>> vnx_queue_offer_trade;
	std::unordered_map<uint64_t, std::pair<std::function<void(std::shared_ptr<const ::mmx::Transaction>)>, std::function<void(const vnx::exception&)>>> vnx_queue_offer_withdraw;
	std::unordered_map<uint64_t, std::pair<std::function<void(std::shared_ptr<const ::mmx::Transaction>)>, std::function<void(const vnx::exception&)>>> vnx_queue_accept_offer;
	std::unordered_map<uint64_t, std::pair<std::function<void(std::shared_ptr<const ::mmx::Transaction>)>, std::function<void(const vnx::exception&)>>> vnx_queue_cancel_offer;
	std::unordered_map<uint64_t, std::pair<std::function<void(std::shared_ptr<const ::mmx::Transaction>)>, std::function<void(const vnx::exception&)>>> vnx_queue_swap_trade;
	std::unordered_map<uint64_t, std::pair<std::function<void(std::shared_ptr<const ::mmx::Transaction>)>, std::function<void(const vnx::exception&)>>> vnx_queue_swap_add_liquid;
	std::unordered_map<uint64_t, std::pair<std::function<void(std::shared_ptr<const ::mmx::Transaction>)>, std::function<void(const vnx::exception&)>>> vnx_queue_swap_rem_liquid;
	std::unordered_map<uint64_t, std::pair<std::function<void(std::shared_ptr<const ::mmx::Transaction>)>, std::function<void(const vnx::exception&)>>> vnx_queue_complete;
	std::unordered_map<uint64_t, std::pair<std::function<void(std::shared_ptr<const ::mmx::Transaction>)>, std::function<void(const vnx::exception&)>>> vnx_queue_sign_off;
	std::unordered_map<uint64_t, std::pair<std::function<void(std::shared_ptr<const ::mmx::Solution>)>, std::function<void(const vnx::exception&)>>> vnx_queue_sign_msg;
	std::unordered_map<uint64_t, std::pair<std::function<void()>, std::function<void(const vnx::exception&)>>> vnx_queue_send_off;
	std::unordered_map<uint64_t, std::pair<std::function<void()>, std::function<void(const vnx::exception&)>>> vnx_queue_mark_spent;
	std::unordered_map<uint64_t, std::pair<std::function<void()>, std::function<void(const vnx::exception&)>>> vnx_queue_reserve;
	std::unordered_map<uint64_t, std::pair<std::function<void()>, std::function<void(const vnx::exception&)>>> vnx_queue_release;
	std::unordered_map<uint64_t, std::pair<std::function<void()>, std::function<void(const vnx::exception&)>>> vnx_queue_release_all;
	std::unordered_map<uint64_t, std::pair<std::function<void()>, std::function<void(const vnx::exception&)>>> vnx_queue_reset_cache;
	std::unordered_map<uint64_t, std::pair<std::function<void()>, std::function<void(const vnx::exception&)>>> vnx_queue_update_cache;
	std::unordered_map<uint64_t, std::pair<std::function<void(const std::vector<::mmx::tx_entry_t>&)>, std::function<void(const vnx::exception&)>>> vnx_queue_get_history;
	std::unordered_map<uint64_t, std::pair<std::function<void(const std::vector<::mmx::tx_entry_t>&)>, std::function<void(const vnx::exception&)>>> vnx_queue_get_history_memo;
	std::unordered_map<uint64_t, std::pair<std::function<void(const std::vector<::mmx::tx_log_entry_t>&)>, std::function<void(const vnx::exception&)>>> vnx_queue_get_tx_log;
	std::unordered_map<uint64_t, std::pair<std::function<void(const std::vector<::mmx::txin_t>&)>, std::function<void(const vnx::exception&)>>> vnx_queue_gather_inputs_for;
	std::unordered_map<uint64_t, std::pair<std::function<void(const ::mmx::balance_t&)>, std::function<void(const vnx::exception&)>>> vnx_queue_get_balance;
	std::unordered_map<uint64_t, std::pair<std::function<void(const std::map<::mmx::addr_t, ::mmx::balance_t>&)>, std::function<void(const vnx::exception&)>>> vnx_queue_get_balances;
	std::unordered_map<uint64_t, std::pair<std::function<void(const std::map<::mmx::addr_t, ::mmx::balance_t>&)>, std::function<void(const vnx::exception&)>>> vnx_queue_get_total_balances;
	std::unordered_map<uint64_t, std::pair<std::function<void(const std::map<::mmx::addr_t, ::mmx::balance_t>&)>, std::function<void(const vnx::exception&)>>> vnx_queue_get_contract_balances;
	std::unordered_map<uint64_t, std::pair<std::function<void(const std::map<::mmx::addr_t, std::shared_ptr<const ::mmx::Contract>>&)>, std::function<void(const vnx::exception&)>>> vnx_queue_get_contracts;
	std::unordered_map<uint64_t, std::pair<std::function<void(const std::map<::mmx::addr_t, std::shared_ptr<const ::mmx::Contract>>&)>, std::function<void(const vnx::exception&)>>> vnx_queue_get_contracts_owned;
	std::unordered_map<uint64_t, std::pair<std::function<void(const std::vector<::mmx::virtual_plot_info_t>&)>, std::function<void(const vnx::exception&)>>> vnx_queue_get_virtual_plots;
	std::unordered_map<uint64_t, std::pair<std::function<void(const std::vector<::mmx::offer_data_t>&)>, std::function<void(const vnx::exception&)>>> vnx_queue_get_offers;
	std::unordered_map<uint64_t, std::pair<std::function<void(const std::map<::mmx::addr_t, std::array<std::pair<::mmx::addr_t, ::mmx::uint128>, 2>>&)>, std::function<void(const vnx::exception&)>>> vnx_queue_get_swap_liquidity;
	std::unordered_map<uint64_t, std::pair<std::function<void(const ::mmx::addr_t&)>, std::function<void(const vnx::exception&)>>> vnx_queue_get_address;
	std::unordered_map<uint64_t, std::pair<std::function<void(const std::vector<::mmx::addr_t>&)>, std::function<void(const vnx::exception&)>>> vnx_queue_get_all_addresses;
	std::unordered_map<uint64_t, std::pair<std::function<void(const ::mmx::account_info_t&)>, std::function<void(const vnx::exception&)>>> vnx_queue_get_account;
	std::unordered_map<uint64_t, std::pair<std::function<void(const std::vector<::mmx::account_info_t>&)>, std::function<void(const vnx::exception&)>>> vnx_queue_get_all_accounts;
	std::unordered_map<uint64_t, std::pair<std::function<void(const vnx::bool_t&)>, std::function<void(const vnx::exception&)>>> vnx_queue_is_locked;
	std::unordered_map<uint64_t, std::pair<std::function<void()>, std::function<void(const vnx::exception&)>>> vnx_queue_lock;
	std::unordered_map<uint64_t, std::pair<std::function<void()>, std::function<void(const vnx::exception&)>>> vnx_queue_unlock;
	std::unordered_map<uint64_t, std::pair<std::function<void()>, std::function<void(const vnx::exception&)>>> vnx_queue_add_account;
	std::unordered_map<uint64_t, std::pair<std::function<void()>, std::function<void(const vnx::exception&)>>> vnx_queue_create_account;
	std::unordered_map<uint64_t, std::pair<std::function<void()>, std::function<void(const vnx::exception&)>>> vnx_queue_create_wallet;
	std::unordered_map<uint64_t, std::pair<std::function<void()>, std::function<void(const vnx::exception&)>>> vnx_queue_import_wallet;
	std::unordered_map<uint64_t, std::pair<std::function<void()>, std::function<void(const vnx::exception&)>>> vnx_queue_remove_account;
	std::unordered_map<uint64_t, std::pair<std::function<void(std::shared_ptr<const ::mmx::KeyFile>)>, std::function<void(const vnx::exception&)>>> vnx_queue_export_wallet;
	std::unordered_map<uint64_t, std::pair<std::function<void(const std::vector<std::string>&)>, std::function<void(const vnx::exception&)>>> vnx_queue_get_mnemonic_wordlist;
	std::unordered_map<uint64_t, std::pair<std::function<void(const std::set<::mmx::addr_t>&)>, std::function<void(const vnx::exception&)>>> vnx_queue_get_token_list;
	std::unordered_map<uint64_t, std::pair<std::function<void()>, std::function<void(const vnx::exception&)>>> vnx_queue_add_token;
	std::unordered_map<uint64_t, std::pair<std::function<void()>, std::function<void(const vnx::exception&)>>> vnx_queue_rem_token;
	std::unordered_map<uint64_t, std::pair<std::function<void(const ::mmx::hash_t&)>, std::function<void(const vnx::exception&)>>> vnx_queue_get_master_seed;
	std::unordered_map<uint64_t, std::pair<std::function<void(const std::vector<std::string>&)>, std::function<void(const vnx::exception&)>>> vnx_queue_get_mnemonic_seed;
	std::unordered_map<uint64_t, std::pair<std::function<void(const std::pair<::mmx::skey_t, ::mmx::pubkey_t>&)>, std::function<void(const vnx::exception&)>>> vnx_queue_get_farmer_keys;
	std::unordered_map<uint64_t, std::pair<std::function<void(const std::vector<std::pair<::mmx::skey_t, ::mmx::pubkey_t>>&)>, std::function<void(const vnx::exception&)>>> vnx_queue_get_all_farmer_keys;
	std::unordered_map<uint64_t, std::pair<std::function<void(std::shared_ptr<const ::vnx::addons::HttpResponse>)>, std::function<void(const vnx::exception&)>>> vnx_queue_http_request;
	std::unordered_map<uint64_t, std::pair<std::function<void(std::shared_ptr<const ::vnx::addons::HttpData>)>, std::function<void(const vnx::exception&)>>> vnx_queue_http_request_chunk;
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

#endif // INCLUDE_mmx_Wallet_ASYNC_CLIENT_HXX_
