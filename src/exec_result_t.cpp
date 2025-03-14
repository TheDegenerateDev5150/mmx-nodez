/*
 * exec_result_t.cpp
 *
 *  Created on: Aug 23, 2022
 *      Author: mad
 */

#include <mmx/exec_result_t.hxx>
#include <mmx/error_code_e.hxx>
#include <mmx/write_bytes.h>


namespace mmx {

vnx::bool_t exec_result_t::is_valid() const
{
	for(const auto& in : inputs) {
		if(in.memo && in.memo->size() > txio_t::MAX_MEMO_SIZE) {
			return false;
		}
	}
	for(const auto& out : outputs) {
		if(out.memo && out.memo->size() > txio_t::MAX_MEMO_SIZE) {
			return false;
		}
	}
	return !error || error->is_valid();
}

hash_t exec_result_t::calc_hash() const
{
	std::vector<uint8_t> buffer;
	vnx::VectorOutputStream stream(&buffer);
	vnx::OutputBuffer out(&stream);

	write_bytes(out, get_type_hash());
	write_field(out, "did_fail", 	did_fail);
	write_field(out, "total_cost", 	total_cost);
	write_field(out, "total_fee", 	total_fee);
	write_field(out, "inputs",		inputs);
	write_field(out, "outputs", 	outputs);
	write_field(out, "error", 		error ? error->calc_hash() : hash_t());
	out.flush();

	return hash_t(buffer);
}

uint64_t exec_result_t::calc_cost(std::shared_ptr<const ChainParams> params) const
{
	uint64_t cost = 0;
	for(const auto& in : inputs) {
		cost += in.calc_cost(params);
	}
	for(const auto& out : outputs) {
		cost += out.calc_cost(params);
	}
	return cost;
}

std::string exec_result_t::get_error_msg() const
{
	if(did_fail) {
		if(error) {
			std::string code;
			if(error->code) {
				const auto name = error_code_e(error_code_e::enum_t(error->code)).to_string_value();
				if(name != std::to_string(error->code)) {
					code = " (" + name + ")";
				} else {
					code = " (code " + name + ")";
				}
			}
			if(error->operation != 0xFFFFFFFF) {
				std::string location;
				if(error->address != 0xFFFFFFFF) {
					location = "exception at 0x" + vnx::to_hex_string(error->address);
					if(error->line) {
						location += ", line " + std::to_string(*error->line);
					}
					location += ": ";
				}
				return location + error->message + code + " (op " + std::to_string(error->operation) + ")";
			} else {
				return error->message + code;
			}
		}
		return "tx failed";
	}
	return std::string();
}


} // mmx
