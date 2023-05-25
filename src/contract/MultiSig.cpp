/*
 * MultiSig.cpp
 *
 *  Created on: Jan 15, 2022
 *      Author: mad
 */

#include <mmx/contract/MultiSig.hxx>
#include <mmx/solution/MultiSig.hxx>
#include <mmx/solution/PubKey.hxx>
#include <mmx/write_bytes.h>
#include <mmx/exception.h>


namespace mmx {
namespace contract {

vnx::bool_t MultiSig::is_valid() const
{
	return Super::is_valid() && num_required > 0 && owners.size() >= num_required;
}

hash_t MultiSig::calc_hash(const vnx::bool_t& full_hash) const
{
	std::vector<uint8_t> buffer;
	vnx::VectorOutputStream stream(&buffer);
	vnx::OutputBuffer out(&stream);

	write_bytes(out, get_type_hash());
	write_field(out, "version", version);
	write_field(out, "owners", owners);
	out.flush();

	return hash_t(buffer);
}

uint64_t MultiSig::calc_cost(std::shared_ptr<const ChainParams> params, const vnx::bool_t& is_read) const
{
	return 8 + 32 * owners.size() * (is_read ? params->min_txfee_read_byte : params->min_txfee_byte);
}

void MultiSig::validate(std::shared_ptr<const Solution> solution, const hash_t& txid) const
{
	if(auto sol = std::dynamic_pointer_cast<const solution::PubKey>(solution))
	{
		if(num_required != 1) {
			throw mmx::invalid_solution("num_required != 1");
		}
		if(owners.count(sol->pubkey.get_addr()))
		{
			if(!sol->signature.verify(sol->pubkey, txid)) {
				throw mmx::invalid_solution("invalid signature");
			}
			return;
		}
		throw mmx::invalid_solution("no such owner");
	}
	if(auto sol = std::dynamic_pointer_cast<const solution::MultiSig>(solution))
	{
		size_t count = 0;
		for(const auto& entry : sol->solutions)
		{
			if(owners.count(entry.first))
			{
				if(auto solution = std::dynamic_pointer_cast<const solution::PubKey>(entry.second))
				{
					if(solution->pubkey.get_addr() != entry.first) {
						throw mmx::invalid_solution("wrong pubkey for " + entry.first.to_string());
					}
					if(!solution->signature.verify(solution->pubkey, txid)) {
						throw mmx::invalid_solution("invalid signature for " + entry.first.to_string());
					}
					count++;
				}
			}
		}
		if(count < num_required) {
			throw mmx::invalid_solution("insufficient signatures: " + std::to_string(count) + " < " + std::to_string(num_required));
		}
		return;
	}
	if(solution) {
		throw mmx::invalid_solution("invalid type");
	} else {
		throw mmx::invalid_solution("missing");
	}
}

vnx::Variant MultiSig::read_field(const std::string& name) const
{
	if(name == "owners") {
		std::vector<std::string> tmp;
		for(const auto& entry : owners) {
			tmp.push_back(entry.to_string());
		}
		return vnx::Variant(tmp);
	}
	return Super::read_field(name);
}


} // contract
} // mmx
