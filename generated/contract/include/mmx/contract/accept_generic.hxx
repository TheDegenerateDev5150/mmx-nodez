
// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_mmx_contract_ACCEPT_GENERIC_HXX_
#define INCLUDE_mmx_contract_ACCEPT_GENERIC_HXX_

#include <mmx/contract/Binary.hxx>
#include <mmx/contract/Data.hxx>
#include <mmx/contract/Executable.hxx>
#include <mmx/contract/MultiSig.hxx>
#include <mmx/contract/PubKey.hxx>
#include <mmx/contract/TokenBase.hxx>
#include <mmx/contract/WebData.hxx>


namespace vnx {

template<typename V>
void accept_generic(V& visitor, std::shared_ptr<const ::mmx::contract::Binary> value) {
	if(value) {
		value->accept_generic(visitor);
	} else {
		visitor.accept(nullptr);
	}
}

template<typename V>
void accept_generic(V& visitor, std::shared_ptr<const ::mmx::contract::Data> value) {
	if(value) {
		value->accept_generic(visitor);
	} else {
		visitor.accept(nullptr);
	}
}

template<typename V>
void accept_generic(V& visitor, std::shared_ptr<const ::mmx::contract::Executable> value) {
	if(value) {
		value->accept_generic(visitor);
	} else {
		visitor.accept(nullptr);
	}
}

template<typename V>
void accept_generic(V& visitor, std::shared_ptr<const ::mmx::contract::MultiSig> value) {
	if(value) {
		value->accept_generic(visitor);
	} else {
		visitor.accept(nullptr);
	}
}

template<typename V>
void accept_generic(V& visitor, std::shared_ptr<const ::mmx::contract::PubKey> value) {
	if(value) {
		value->accept_generic(visitor);
	} else {
		visitor.accept(nullptr);
	}
}

template<typename V>
void accept_generic(V& visitor, std::shared_ptr<const ::mmx::contract::TokenBase> value) {
	if(value) {
		if(auto tmp = std::dynamic_pointer_cast<const ::mmx::contract::Executable>(value)) {
			vnx::accept_generic(visitor, tmp);
		} else {
			value->accept_generic(visitor);
		}
	} else {
		visitor.accept(nullptr);
	}
}

template<typename V>
void accept_generic(V& visitor, std::shared_ptr<const ::mmx::contract::WebData> value) {
	if(value) {
		value->accept_generic(visitor);
	} else {
		visitor.accept(nullptr);
	}
}



} // namespace vnx

#endif // INCLUDE_mmx_contract_ACCEPT_GENERIC_HXX_
