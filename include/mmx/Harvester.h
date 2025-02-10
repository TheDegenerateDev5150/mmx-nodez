/*
 * Harvester.h
 *
 *  Created on: Dec 11, 2021
 *      Author: mad
 */

#ifndef INCLUDE_MMX_HARVESTER_H_
#define INCLUDE_MMX_HARVESTER_H_

#include <mmx/HarvesterBase.hxx>
#include <mmx/FarmerClient.hxx>
#include <mmx/FarmerAsyncClient.hxx>
#include <mmx/NodeAsyncClient.hxx>
#include <mmx/virtual_plot_info_t.hxx>
#include <mmx/pos/Prover.h>

#include <vnx/ThreadPool.h>
#include <vnx/addons/HttpInterface.h>


namespace mmx {

class Harvester : public HarvesterBase {
public:
	Harvester(const std::string& _vnx_name);

protected:
	void init() override;

	void main() override;

	void handle(std::shared_ptr<const Challenge> value) override;

	void reload() override;

	void add_plot_dir(const std::string& path) override;

	void rem_plot_dir(const std::string& path) override;

	uint64_t get_total_bytes() const override;

	std::shared_ptr<const FarmInfo> get_farm_info() const override;

	void http_request_async(std::shared_ptr<const vnx::addons::HttpRequest> request, const std::string& sub_path,
							const vnx::request_id_t& request_id) const override;

	void http_request_chunk_async(	std::shared_ptr<const vnx::addons::HttpRequest> request, const std::string& sub_path,
									const int64_t& offset, const int64_t& max_bytes, const vnx::request_id_t& request_id) const override;

private:
	void update();
	void update_nfts();

	void check_queue();

	std::vector<uint32_t> fetch_full_proof(
			std::shared_ptr<pos::Prover> prover, const uint64_t index) const;

	void lookup_task(std::shared_ptr<const Challenge> value, const int64_t recv_time_ms) const;

	void find_plot_dirs(const std::set<std::string>& dirs, std::set<std::string>& all_dirs, const size_t depth) const;

	// thread safe
	void send_response(	std::shared_ptr<const Challenge> request, std::shared_ptr<const ProofOfSpace> proof,
						const int64_t time_begin_ms) const;

private:
	bool is_ready = false;
	hash_t harvester_id;
	uint64_t total_bytes = 0;
	uint64_t total_bytes_effective = 0;

	vnx::Hash64 farmer_addr;
	std::shared_ptr<FarmerClient> farmer;
	std::shared_ptr<FarmerAsyncClient> farmer_async;
	std::shared_ptr<NodeAsyncClient> node_async;
	std::shared_ptr<vnx::ThreadPool> threads;
	std::shared_ptr<const ChainParams> params;

	std::unordered_set<hash_t> already_checked;
	std::unordered_map<hash_t, std::string> id_map;
	std::unordered_map<std::string, std::shared_ptr<pos::Prover>> plot_map;

	std::map<addr_t, uint32_t> plot_contract_set;
	std::map<addr_t, plot_nft_info_t> plot_nfts;
	std::map<addr_t, uint64_t> partial_diff;

	struct lookup_t {
		int64_t recv_time_ms = 0;
		std::shared_ptr<const Challenge> request;
	};
	std::map<uint32_t, lookup_t> lookup_queue;

	std::shared_ptr<vnx::Timer> lookup_timer;
	std::shared_ptr<vnx::addons::HttpInterface<Harvester>> http;

	mutable std::mutex mutex;

	friend class vnx::addons::HttpInterface<Harvester>;

};


} // mmx

#endif /* INCLUDE_MMX_HARVESTER_H_ */
