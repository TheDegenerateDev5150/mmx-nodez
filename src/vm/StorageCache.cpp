/*
 * StorageCache.cpp
 *
 *  Created on: May 6, 2022
 *      Author: mad
 */

#include <mmx/vm/StorageCache.h>


namespace mmx {
namespace vm {

StorageCache::StorageCache(std::shared_ptr<Storage> backend)
	:	backend(backend)
{
}

StorageCache::~StorageCache()
{
}

std::unique_ptr<var_t> StorageCache::read(const addr_t& contract, const uint64_t src) const
{
	if(auto var = Super::read(contract, src)) {
		return var;
	}
	return backend->read(contract, src);
}

std::unique_ptr<var_t> StorageCache::read(const addr_t& contract, const uint64_t src, const uint64_t key) const
{
	if(auto var = Super::read(contract, src, key)) {
		return var;
	}
	return backend->read(contract, src, key);
}

uint64_t StorageCache::lookup(const addr_t& contract, const var_t& value) const
{
	if(auto key = Super::lookup(contract, value)) {
		return key;
	}
	return backend->lookup(contract, value);
}

void StorageCache::commit() const
{
	for(const auto& entry : memory) {
		if(auto var = entry.second.get()) {
			backend->write(entry.first.first, entry.first.second, *var);
		}
	}
	for(const auto& entry : entries) {
		if(auto var = entry.second.get()) {
			backend->write(std::get<0>(entry.first), std::get<1>(entry.first), std::get<2>(entry.first), *var);
		}
	}
	for(const auto& entry : balance_map) {
		for(const auto& entry2 : entry.second) {
			backend->set_balance(entry.first, entry2.first, entry2.second);
		}
	}
}

std::unique_ptr<uint128> StorageCache::get_balance(const addr_t& contract, const addr_t& currency)
{
	if(auto value = Super::get_balance(contract, currency)) {
		return value;
	}
	auto amount = backend->get_balance(contract, currency);
	if(amount) {
		Super::set_balance(contract, currency, *amount);
	}
	return amount;
}


} // vm
} // mmx
