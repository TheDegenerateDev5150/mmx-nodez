/*
 * create_swap_binary.cpp
 *
 *  Created on: Oct 29, 2022
 *      Author: mad
 */

#include <mmx/vm/var_t.h>
#include <mmx/vm/instr_t.h>
#include <mmx/vm/varptr_t.hpp>
#include <mmx/vm/Engine.h>

#include <mmx/contract/Binary.hxx>

using namespace mmx;


int main(int argc, char** argv)
{
	auto bin = mmx::contract::Binary::create();
	bin->name = "mmx/swap";

	constexpr int FRACT_BITS = 64;

	std::vector<vm::varptr_t> constant;
	std::map<std::string, size_t> const_map;

	const_map["null"] = constant.size();
	constant.push_back(std::make_unique<vm::var_t>());

	const_map["array"] = constant.size();
	constant.push_back(std::make_unique<vm::array_t>());

	const_map["map"] = constant.size();
	constant.push_back(std::make_unique<vm::map_t>());

	const_map["0"] = constant.size();
	constant.push_back(std::make_unique<vm::uint_t>(0));

	const_map["1"] = constant.size();
	constant.push_back(std::make_unique<vm::uint_t>(1));

	const_map["2"] = constant.size();
	constant.push_back(std::make_unique<vm::uint_t>(2));

	const_map["FRACT_BITS"] = constant.size();
	constant.push_back(std::make_unique<vm::uint_t>(FRACT_BITS));

	const_map["balance"] = constant.size();
	constant.push_back(vm::binary_t::alloc("balance"));

	const_map["last_user_total"] = constant.size();
	constant.push_back(vm::binary_t::alloc("last_user_total"));

	const_map["last_fees_paid"] = constant.size();
	constant.push_back(vm::binary_t::alloc("last_fees_paid"));

	const_map["max_fee_rate"] = constant.size();
	constant.push_back(std::make_unique<vm::uint_t>((uint256_t(1) << FRACT_BITS) / 4));

	const_map["min_fee_rate"] = constant.size();
	constant.push_back(std::make_unique<vm::uint_t>((uint256_t(1) << FRACT_BITS) / 2048));

	const_map["fail_amount"] = constant.size();
	constant.push_back(vm::binary_t::alloc("invalid amount"));

	const_map["fail_currency"] = constant.size();
	constant.push_back(vm::binary_t::alloc("currency mismatch"));

	const_map["fail_user"] = constant.size();
	constant.push_back(vm::binary_t::alloc("invalid user"));

	{
		size_t off = 1;
		bin->fields["tokens"] = vm::MEM_STATIC + (off++);
		bin->fields["user_total"] = vm::MEM_STATIC + (off++);
		bin->fields["trade_volume"] = vm::MEM_STATIC + (off++);
		bin->fields["fees_paid"] = vm::MEM_STATIC + (off++);
		bin->fields["fees_claimed"] = vm::MEM_STATIC + (off++);
		bin->fields["users"] = vm::MEM_STATIC + (off++);
	}

	std::vector<vm::instr_t> code;
	{
		mmx::contract::method_t method;
		method.name = "init";
		method.args = {"token", "currency"};
		method.entry_point = code.size();
		code.emplace_back(vm::OP_COPY, 0, bin->fields["tokens"], const_map["array"]);
		code.emplace_back(vm::OP_CONV, 0, vm::MEM_STACK + 11, vm::MEM_STACK + 1, vm::CONVTYPE_UINT, vm::CONVTYPE_ADDRESS);
		code.emplace_back(vm::OP_SET,  0, bin->fields["tokens"], const_map["0"], vm::MEM_STACK + 11);
		code.emplace_back(vm::OP_CONV, 0, vm::MEM_STACK + 11, vm::MEM_STACK + 2, vm::CONVTYPE_UINT, vm::CONVTYPE_ADDRESS);
		code.emplace_back(vm::OP_SET,  0, bin->fields["tokens"], const_map["1"], vm::MEM_STACK + 11);
		code.emplace_back(vm::OP_COPY, 0, bin->fields["user_total"], const_map["array"]);
		code.emplace_back(vm::OP_SET,  0, bin->fields["user_total"], const_map["0"], const_map["0"]);
		code.emplace_back(vm::OP_SET,  0, bin->fields["user_total"], const_map["1"], const_map["0"]);
		code.emplace_back(vm::OP_COPY, 0, bin->fields["trade_volume"], const_map["array"]);
		code.emplace_back(vm::OP_SET,  0, bin->fields["trade_volume"], const_map["0"], const_map["0"]);
		code.emplace_back(vm::OP_SET,  0, bin->fields["trade_volume"], const_map["1"], const_map["0"]);
		code.emplace_back(vm::OP_COPY, 0, bin->fields["fees_paid"], const_map["array"]);
		code.emplace_back(vm::OP_SET,  0, bin->fields["fees_paid"], const_map["0"], const_map["0"]);
		code.emplace_back(vm::OP_SET,  0, bin->fields["fees_paid"], const_map["1"], const_map["0"]);
		code.emplace_back(vm::OP_COPY, 0, bin->fields["fees_claimed"], const_map["array"]);
		code.emplace_back(vm::OP_SET,  0, bin->fields["fees_claimed"], const_map["0"], const_map["0"]);
		code.emplace_back(vm::OP_SET,  0, bin->fields["fees_claimed"], const_map["1"], const_map["0"]);
		code.emplace_back(vm::OP_COPY, 0, bin->fields["users"], const_map["map"]);
		code.emplace_back(vm::OP_RET);
		bin->methods[method.name] = method;
	}
	{
		mmx::contract::method_t method;
		method.is_public = true;
		method.is_payable = true;
		method.name = "add_liquid";
		method.args = {"index"};
		method.entry_point = code.size();
		// check deposit currency
		code.emplace_back(vm::OP_GET, vm::OPFLAG_HARD_FAIL, vm::MEM_STACK + 11, bin->fields["tokens"], vm::MEM_STACK + 1);
		code.emplace_back(vm::OP_GET, vm::OPFLAG_HARD_FAIL, vm::MEM_STACK + 12, vm::MEM_EXTERN + vm::EXTERN_DEPOSIT, const_map["0"]);
		code.emplace_back(vm::OP_CMP_EQ, 0, vm::MEM_STACK + 10, vm::MEM_STACK + 11, vm::MEM_STACK + 12);
		code.emplace_back(vm::OP_JUMPI, 0, code.size() + 2, vm::MEM_STACK + 10);
		code.emplace_back(vm::OP_FAIL, 0, const_map["fail_currency"]);
		// get user
		code.emplace_back(vm::OP_GET, 0, vm::MEM_STACK + 12, bin->fields["users"], vm::MEM_EXTERN + vm::EXTERN_USER);
		code.emplace_back(vm::OP_CMP_EQ, 0, vm::MEM_STACK + 10, vm::MEM_STACK + 12, const_map["null"]);
		const auto jump_base = code.size();
		code.emplace_back(vm::OP_JUMPN, 0, 0, vm::MEM_STACK + 10);
		// create user
		code.emplace_back(vm::OP_CLONE, 0, vm::MEM_STACK + 12, const_map["map"]);
		code.emplace_back(vm::OP_CLONE, 0, vm::MEM_STACK + 13, const_map["array"]);
		code.emplace_back(vm::OP_SET, vm::OPFLAG_REF_A, vm::MEM_STACK + 13, const_map["0"], const_map["0"]);
		code.emplace_back(vm::OP_SET, vm::OPFLAG_REF_A, vm::MEM_STACK + 13, const_map["1"], const_map["0"]);
		code.emplace_back(vm::OP_SET, vm::OPFLAG_REF_A, vm::MEM_STACK + 12, const_map["balance"], vm::MEM_STACK + 13);
		code.emplace_back(vm::OP_CLONE, 0, vm::MEM_STACK + 13, const_map["array"]);
		code.emplace_back(vm::OP_SET, vm::OPFLAG_REF_A, vm::MEM_STACK + 13, const_map["0"], const_map["0"]);
		code.emplace_back(vm::OP_SET, vm::OPFLAG_REF_A, vm::MEM_STACK + 13, const_map["1"], const_map["0"]);
		code.emplace_back(vm::OP_SET, vm::OPFLAG_REF_A, vm::MEM_STACK + 12, const_map["last_user_total"], vm::MEM_STACK + 13);
		code.emplace_back(vm::OP_CLONE, 0, vm::MEM_STACK + 13, const_map["array"]);
		code.emplace_back(vm::OP_SET, vm::OPFLAG_REF_A, vm::MEM_STACK + 13, const_map["0"], const_map["0"]);
		code.emplace_back(vm::OP_SET, vm::OPFLAG_REF_A, vm::MEM_STACK + 13, const_map["1"], const_map["0"]);
		code.emplace_back(vm::OP_SET, vm::OPFLAG_REF_A, vm::MEM_STACK + 12, const_map["last_fees_paid"], vm::MEM_STACK + 13);
		code.emplace_back(vm::OP_SET, 0, bin->fields["users"], vm::MEM_EXTERN + vm::EXTERN_USER, vm::MEM_STACK + 12);
		code[jump_base].a = code.size();
		// get deposit amount
		code.emplace_back(vm::OP_GET, vm::OPFLAG_HARD_FAIL, vm::MEM_STACK + 13, vm::MEM_EXTERN + vm::EXTERN_DEPOSIT, const_map["1"]);
		// user_total[i] += amount[i];
		code.emplace_back(vm::OP_GET, vm::OPFLAG_HARD_FAIL, vm::MEM_STACK + 14, bin->fields["user_total"], vm::MEM_STACK + 1);
		code.emplace_back(vm::OP_ADD, vm::OPFLAG_CATCH_OVERFLOW, vm::MEM_STACK + 14, vm::MEM_STACK + 14, vm::MEM_STACK + 13);
		code.emplace_back(vm::OP_SET, 0, bin->fields["user_total"], vm::MEM_STACK + 1, vm::MEM_STACK + 14);
		// user.last_user_total[i] = user_total[i];
		code.emplace_back(vm::OP_GET, vm::OPFLAG_HARD_FAIL | vm::OPFLAG_REF_B, vm::MEM_STACK + 15, vm::MEM_STACK + 12, const_map["last_user_total"]);
		code.emplace_back(vm::OP_SET, vm::OPFLAG_REF_A, vm::MEM_STACK + 15, vm::MEM_STACK + 1, vm::MEM_STACK + 14);
		// user.balance[i] += amount[i];
		code.emplace_back(vm::OP_GET, vm::OPFLAG_HARD_FAIL | vm::OPFLAG_REF_B, vm::MEM_STACK + 14, vm::MEM_STACK + 12, const_map["balance"]);
		code.emplace_back(vm::OP_GET, vm::OPFLAG_HARD_FAIL, vm::MEM_STACK + 15, vm::MEM_STACK + 14, vm::MEM_STACK + 1);
		code.emplace_back(vm::OP_ADD, vm::OPFLAG_CATCH_OVERFLOW, vm::MEM_STACK + 15, vm::MEM_STACK + 15, vm::MEM_STACK + 13);
		code.emplace_back(vm::OP_SET, vm::OPFLAG_REF_A, vm::MEM_STACK + 14, vm::MEM_STACK + 1, vm::MEM_STACK + 15);
		code.emplace_back(vm::OP_RET);
		bin->methods[method.name] = method;
	}
	{
		mmx::contract::method_t method;
		method.is_public = true;
		method.name = "rem_liquid";
		method.args = {"index", "amount"};
		method.entry_point = code.size();
		// TODO
		code.emplace_back(vm::OP_RET);
		bin->methods[method.name] = method;
	}
	{
		mmx::contract::method_t method;
		method.is_public = true;
		method.name = "trade";
		method.args = {"index", "amount"};
		method.entry_point = code.size();
		// TODO
		code.emplace_back(vm::OP_RET);
		bin->methods[method.name] = method;
	}
	{
		mmx::contract::method_t method;
		method.is_public = true;
		method.name = "payout";
		method.entry_point = code.size();
		code.emplace_back(vm::OP_GET,  0, vm::MEM_STACK + 12, bin->fields["users"], vm::MEM_EXTERN + vm::EXTERN_USER);
		code.emplace_back(vm::OP_CMP_EQ, 0, vm::MEM_STACK + 10, vm::MEM_STACK + 12, const_map["null"]);
		code.emplace_back(vm::OP_JUMPN,  0, code.size() + 2, vm::MEM_STACK + 10);
		code.emplace_back(vm::OP_FAIL, 0, const_map["fail_user"]);
		// for(int i = 0; i < 2; ++i) {
		code.emplace_back(vm::OP_COPY, 0, vm::MEM_STACK + 13, const_map["0"]);
		const auto for_begin = code.size();
		code.emplace_back(vm::OP_GET, vm::OPFLAG_HARD_FAIL | vm::OPFLAG_REF_B, vm::MEM_STACK + 14, vm::MEM_STACK + 12, const_map["balance"]);
		code.emplace_back(vm::OP_GET, vm::OPFLAG_HARD_FAIL, vm::MEM_STACK + 14, vm::MEM_STACK + 14, vm::MEM_STACK + 13);
		// if(user.balance[i]) {
		code.emplace_back(vm::OP_CMP_EQ, 0, vm::MEM_STACK + 10, vm::MEM_STACK + 14, const_map["0"]);
		const auto jump_base = code.size();
		code.emplace_back(vm::OP_JUMPI, 0, 0, vm::MEM_STACK + 10);
		// const auto total_fees = fees_paid[i] - user.last_fees_paid[i];
		code.emplace_back(vm::OP_GET, vm::OPFLAG_HARD_FAIL, vm::MEM_STACK + 15, bin->fields["fees_paid"], vm::MEM_STACK + 13);
		code.emplace_back(vm::OP_GET, vm::OPFLAG_HARD_FAIL | vm::OPFLAG_REF_B, vm::MEM_STACK + 16, vm::MEM_STACK + 12, const_map["last_fees_paid"]);
		code.emplace_back(vm::OP_GET, vm::OPFLAG_HARD_FAIL | vm::OPFLAG_REF_B, vm::MEM_STACK + 16, vm::MEM_STACK + 16, vm::MEM_STACK + 13);
		code.emplace_back(vm::OP_SUB, vm::OPFLAG_CATCH_OVERFLOW, vm::MEM_STACK + 17, vm::MEM_STACK + 15, vm::MEM_STACK + 16);
		// auto user_share = (2 * total_fees * user.balance[i]) / (user_total[i] + user.last_user_total[i]);
		code.emplace_back(vm::OP_MUL, vm::OPFLAG_CATCH_OVERFLOW, vm::MEM_STACK + 18, vm::MEM_STACK + 17, const_map["2"]);
		code.emplace_back(vm::OP_MUL, vm::OPFLAG_CATCH_OVERFLOW, vm::MEM_STACK + 18, vm::MEM_STACK + 18, vm::MEM_STACK + 14);
		code.emplace_back(vm::OP_GET, vm::OPFLAG_HARD_FAIL, vm::MEM_STACK + 19, bin->fields["user_total"], vm::MEM_STACK + 13);
		code.emplace_back(vm::OP_GET, vm::OPFLAG_HARD_FAIL | vm::OPFLAG_REF_B, vm::MEM_STACK + 20, vm::MEM_STACK + 12, const_map["last_user_total"]);
		code.emplace_back(vm::OP_GET, vm::OPFLAG_HARD_FAIL | vm::OPFLAG_REF_B, vm::MEM_STACK + 20, vm::MEM_STACK + 20, vm::MEM_STACK + 13);
		code.emplace_back(vm::OP_ADD, vm::OPFLAG_CATCH_OVERFLOW, vm::MEM_STACK + 19, vm::MEM_STACK + 19, vm::MEM_STACK + 20);
		code.emplace_back(vm::OP_DIV, vm::OPFLAG_CATCH_OVERFLOW, vm::MEM_STACK + 18, vm::MEM_STACK + 18, vm::MEM_STACK + 19);
		// user_share = std::min(user_share, balance[i]);
		code.emplace_back(vm::OP_GET, vm::OPFLAG_HARD_FAIL, vm::MEM_STACK + 20, bin->fields["tokens"], vm::MEM_STACK + 13);
		code.emplace_back(vm::OP_GET, vm::OPFLAG_HARD_FAIL, vm::MEM_STACK + 19, vm::MEM_EXTERN + vm::EXTERN_BALANCE, vm::MEM_STACK + 20);
		code.emplace_back(vm::OP_MIN, 0, vm::MEM_STACK + 18, vm::MEM_STACK + 18, vm::MEM_STACK + 19);
		// send earned fees
		code.emplace_back(vm::OP_SEND, 0, vm::MEM_EXTERN + vm::EXTERN_USER, vm::MEM_STACK + 18, vm::MEM_STACK + 20);
		// fees_claimed[i] += user_share;
		code.emplace_back(vm::OP_GET, 0, vm::MEM_STACK + 21, bin->fields["fees_claimed"], vm::MEM_STACK + 13);
		code.emplace_back(vm::OP_ADD, vm::OPFLAG_CATCH_OVERFLOW, vm::MEM_STACK + 21, vm::MEM_STACK + 21, vm::MEM_STACK + 18);
		code.emplace_back(vm::OP_SET, 0, bin->fields["fees_claimed"], vm::MEM_STACK + 13, vm::MEM_STACK + 21);
		code[jump_base].a = code.size();
		// user.last_user_total[i] = user_total[i];
		code.emplace_back(vm::OP_GET, vm::OPFLAG_HARD_FAIL, vm::MEM_STACK + 14, bin->fields["user_total"], vm::MEM_STACK + 13);
		code.emplace_back(vm::OP_GET, vm::OPFLAG_HARD_FAIL | vm::OPFLAG_REF_B, vm::MEM_STACK + 15, vm::MEM_STACK + 12, const_map["last_user_total"]);
		code.emplace_back(vm::OP_SET, vm::OPFLAG_REF_A, vm::MEM_STACK + 15, vm::MEM_STACK + 13, vm::MEM_STACK + 14);
		// user.last_fees_paid[i] = fees_paid[i];
		code.emplace_back(vm::OP_GET, vm::OPFLAG_HARD_FAIL, vm::MEM_STACK + 14, bin->fields["fees_paid"], vm::MEM_STACK + 13);
		code.emplace_back(vm::OP_GET, vm::OPFLAG_HARD_FAIL | vm::OPFLAG_REF_B, vm::MEM_STACK + 15, vm::MEM_STACK + 12, const_map["last_fees_paid"]);
		code.emplace_back(vm::OP_SET, vm::OPFLAG_REF_A, vm::MEM_STACK + 15, vm::MEM_STACK + 13, vm::MEM_STACK + 14);
		// for(int i = 0; i < 2; ++i) {
		code.emplace_back(vm::OP_ADD, 0, vm::MEM_STACK + 13, vm::MEM_STACK + 13, const_map["1"]);
		code.emplace_back(vm::OP_CMP_LT, 0, vm::MEM_STACK + 10, vm::MEM_STACK + 13, const_map["2"]);
		code.emplace_back(vm::OP_JUMPI, 0, for_begin, vm::MEM_STACK + 10);
		code.emplace_back(vm::OP_RET);
		bin->methods[method.name] = method;
	}

	for(const auto& var : constant) {
		const auto data = serialize(*var.get(), false, false);
		bin->constant.insert(bin->constant.end(), data.first.get(), data.first.get() + data.second);
	}
	{
		const auto data = vm::serialize(code);
		bin->binary = std::vector<uint8_t>(data.first.get(), data.first.get() + data.second);

		std::vector<vm::instr_t> test;
		auto length = vm::deserialize(test, data.first.get(), data.second);
		if(length != data.second) {
			throw std::logic_error("length != data.second");
		}
		if(test.size() != code.size()) {
			throw std::logic_error("test.size() != code.size()");
		}
		for(size_t i = 0; i < test.size(); ++i) {
			if(test[i].code != code[i].code) {
				throw std::logic_error("test[i].code != code[i].code");
			}
		}
	}
	vnx::write_to_file(argc > 1 ? argv[1] : "swap_binary.dat", bin);

	return 0;
}





