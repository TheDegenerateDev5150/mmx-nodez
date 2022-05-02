/*
 * test_engine.cpp
 *
 *  Created on: May 1, 2022
 *      Author: mad
 */

#include <mmx/vm/Engine.h>
#include <mmx/vm/StorageRAM.h>
#include <mmx/vm/StorageProxy.h>

#include <iostream>

using namespace mmx;


int main(int arcv, char** argv)
{
	auto backend = std::make_shared<vm::StorageRAM>();
	{
		vm::Engine engine(addr_t(), backend, false);
		engine.write(vm::MEM_CONST + 0, vm::var_t());
		engine.write(vm::MEM_CONST + 1, vm::uint_t(1337));
		engine.write(vm::MEM_CONST + 2, vm::map_t());
		engine.assign(vm::MEM_CONST + 3, vm::binary_t::alloc("value"));
		engine.write(vm::MEM_CONST + 4, vm::uint_t(11337));
		engine.write(vm::MEM_CONST + 5, vm::array_t());

		auto& code = engine.code;
		code.emplace_back(vm::OP_NOP);
		code.emplace_back(vm::OP_CLONE, 0, vm::MEM_STACK + 1, vm::MEM_CONST + 1);
		code.emplace_back(vm::OP_COPY, vm::OPFLAG_REF_B, vm::MEM_STACK + 0, vm::MEM_STACK + 1);
		code.emplace_back(vm::OP_COPY, 0, vm::MEM_STATIC + 0, vm::MEM_CONST + 2);
		code.emplace_back(vm::OP_CLONE, 0, vm::MEM_STACK + 3, vm::MEM_CONST + 3);
		code.emplace_back(vm::OP_SET, 0, vm::MEM_STATIC + 0, vm::MEM_CONST + 3, vm::MEM_CONST + 1);
		code.emplace_back(vm::OP_SET, vm::OPFLAG_REF_B, vm::MEM_STATIC + 0, vm::MEM_STACK + 3, vm::MEM_CONST + 4);
		code.emplace_back(vm::OP_GET, 0, vm::MEM_STACK + 2, vm::MEM_STATIC + 0, vm::MEM_CONST + 3);
		code.emplace_back(vm::OP_COPY, 0, vm::MEM_STATIC + 1, vm::MEM_CONST + 5);
		code.emplace_back(vm::OP_PUSH_BACK, vm::OPFLAG_REF_A, vm::MEM_STATIC + 1, vm::MEM_CONST + 1);
		code.emplace_back(vm::OP_PUSH_BACK, vm::OPFLAG_REF_A, vm::MEM_STATIC + 1, vm::MEM_CONST + 4);
		code.emplace_back(vm::OP_PUSH_BACK, vm::OPFLAG_REF_A, vm::MEM_STATIC + 1, vm::MEM_CONST + 3);
		code.emplace_back(vm::OP_RET);

		engine.credits = 10000;
		engine.begin(0);
		engine.run();
		engine.dump_memory();
		std::cout << "Cost: " << engine.cost << std::endl;
		engine.reset();
	}
	return 0;
}


