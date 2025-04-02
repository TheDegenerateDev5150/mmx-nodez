/*
 * hash_t.cpp
 *
 *  Created on: Jan 6, 2022
 *      Author: mad
 */

#include <mmx/hash_t.hpp>
#include <vnx/SHA256.h>
#include <vnx/Util.h>

#include <uint256_t.h>
#include <sha256_ni.h>
#include <sha256_arm.h>

#include <atomic>
#include <thread>
#include <chrono>


namespace mmx {

static const bytes_t<32> empty_hash("e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");

hash_t::hash_t(const void* data, const size_t num_bytes)
{
	static const bool have_sha_ni = sha256_ni_available();
	static const bool have_sha_arm = sha256_arm_available();

	if(num_bytes == 0) {
		bytes = empty_hash.bytes;
	} else if(have_sha_ni) {
		sha256_ni(bytes.data(), (const uint8_t*)data, num_bytes);
	} else if(have_sha_arm) {
		sha256_arm(bytes.data(), (const uint8_t*)data, num_bytes);
	} else {
		vnx::SHA256 ctx;
		ctx.update((const uint8_t*)data, num_bytes);
		ctx.finalize(bytes.data());
	}
}

hash_t hash_t::random()
{
	hash_t out;
	vnx::secure_random_bytes(out.data(), out.size());
	return out;
}

hash_t hash_t::secure_random()
{
	uint256_t entropy = 0;
	static constexpr int BITS_PER_ITER = 4;
	for(int i = 0; i < 256 / BITS_PER_ITER; ++i)
	{
		entropy <<= BITS_PER_ITER;
		std::atomic_bool trigger {false};

		std::thread timer([&trigger]() {
			std::this_thread::sleep_for(std::chrono::microseconds(10));
			trigger = true;
		});
		while(!trigger) {
			entropy++;
		}
		timer.join();
	}
	const bytes_t<32> entropy_bytes(&entropy, sizeof(entropy));

	bytes_t<128> rand_bytes;
	vnx::secure_random_bytes(rand_bytes.data(), rand_bytes.size());

	return hash_t(entropy_bytes + rand_bytes);
}


} // mmx
