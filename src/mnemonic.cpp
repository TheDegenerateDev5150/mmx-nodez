/*
 * mnemonic.cpp
 *
 *  Created on: Sep 12, 2022
 *      Author: mad
 */

#include <mmx/mnemonic.h>

#include <vnx/Util.h>
#include <algorithm>


namespace mmx {
namespace mnemonic {

std::vector<std::string> seed_to_words(const hash_t& seed, const std::vector<std::string>& wordlist)
{
	if(wordlist.size() != 2048) {
		throw std::logic_error("wordlist.size() != 2048");
	}
	auto bits = seed.to_uint256();
	const auto checksum = hash_t(bytes_t<32>().from_uint(bits, true))[0];

	std::vector<std::string> words;
	for(int i = 0; i < 24; ++i) {
		uint16_t index = 0;
		if(i == 0) {
			index = (bits & 0x7) << 8;
			index |= (checksum & 0xFF);
			bits >>= 3;
		} else {
			index = (bits & 0x7FF);
			bits >>= 11;
		}
		words.push_back(wordlist[index]);
	}
	std::reverse(words.begin(), words.end());
	return words;
}

hash_t words_to_seed(const std::vector<std::string>& words, const std::vector<std::string>& wordlist)
{
	if(words.size() != 24) {
		throw std::logic_error("words.size() != 24");
	}
	if(wordlist.size() != 2048) {
		throw std::logic_error("wordlist.size() != 2048");
	}
	std::unordered_map<std::string, uint16_t> word_map;
	for(size_t i = 0; i < wordlist.size(); ++i) {
		word_map[wordlist[i]] = i;
	}
	uint256_t seed = 0;
	uint8_t checksum = 0;

	for(int i = 0; i < 24; ++i) {
		const auto iter = word_map.find(words[i]);
		if(iter == word_map.end()) {
			throw std::runtime_error("invalid mnemonic word: '" + words[i] + "'");
		}
		if(i < 23) {
			seed <<= 11;
			seed |= iter->second;
		} else {
			seed <<= 3;
			seed |= (iter->second >> 8);
			checksum = (iter->second & 0xFF);
		}
	}
	const auto expect_le = hash_t(bytes_t<32>().from_uint(seed, false))[0];
	const auto expect_be = hash_t(bytes_t<32>().from_uint(seed, true))[0];
	if(checksum != expect_le && checksum != expect_be) {
		throw std::runtime_error("mnemonic checksum failed");
	}
	hash_t out;
	out.from_uint(seed);
	return out;
}

std::string words_to_string(const std::vector<std::string>& words)
{
	std::string out;
	for(size_t i = 0; i < words.size(); ++i) {
		if(i) {
			out += " ";
		}
		out += words[i];
	}
	return out;
}

std::vector<std::string> string_to_words(const std::string& phrase)
{
	return vnx::string_split(phrase, ' ', true);
}


} // mnemonic
} // mmx
