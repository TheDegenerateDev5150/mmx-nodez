/*
 * method_t.cpp
 *
 *  Created on: May 15, 2022
 *      Author: mad
 */

#include <mmx/contract/method_t.hxx>


namespace mmx {
namespace contract {

uint64_t method_t::num_bytes() const
{
	uint64_t payload = 8;
	for(const auto& entry : args) {
		payload += 4 + entry.size();
	}
	payload += 8 + name.size() + info.size();
	return payload;
}


} // contract
} // mmx
