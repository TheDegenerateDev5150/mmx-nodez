
// AUTO GENERATED by vnxcppcodegen

#include <mmx/package.hxx>
#include <mmx/FarmerBase.hxx>
#include <vnx/NoSuchMethod.hxx>
#include <mmx/BlockHeader.hxx>
#include <mmx/FarmInfo.hxx>
#include <mmx/Farmer_get_farm_info.hxx>
#include <mmx/Farmer_get_farm_info_return.hxx>
#include <mmx/Farmer_get_farmer_keys.hxx>
#include <mmx/Farmer_get_farmer_keys_return.hxx>
#include <mmx/Farmer_get_mac_addr.hxx>
#include <mmx/Farmer_get_mac_addr_return.hxx>
#include <mmx/Farmer_sign_block.hxx>
#include <mmx/Farmer_sign_block_return.hxx>
#include <mmx/Farmer_sign_proof.hxx>
#include <mmx/Farmer_sign_proof_return.hxx>
#include <mmx/ProofOfSpace.hxx>
#include <mmx/addr_t.hpp>
#include <mmx/bls_pubkey_t.hpp>
#include <mmx/bls_signature_t.hpp>
#include <vnx/Hash64.hpp>
#include <vnx/Module.h>
#include <vnx/ModuleInterface_vnx_get_config.hxx>
#include <vnx/ModuleInterface_vnx_get_config_return.hxx>
#include <vnx/ModuleInterface_vnx_get_config_object.hxx>
#include <vnx/ModuleInterface_vnx_get_config_object_return.hxx>
#include <vnx/ModuleInterface_vnx_get_module_info.hxx>
#include <vnx/ModuleInterface_vnx_get_module_info_return.hxx>
#include <vnx/ModuleInterface_vnx_get_type_code.hxx>
#include <vnx/ModuleInterface_vnx_get_type_code_return.hxx>
#include <vnx/ModuleInterface_vnx_restart.hxx>
#include <vnx/ModuleInterface_vnx_restart_return.hxx>
#include <vnx/ModuleInterface_vnx_self_test.hxx>
#include <vnx/ModuleInterface_vnx_self_test_return.hxx>
#include <vnx/ModuleInterface_vnx_set_config.hxx>
#include <vnx/ModuleInterface_vnx_set_config_return.hxx>
#include <vnx/ModuleInterface_vnx_set_config_object.hxx>
#include <vnx/ModuleInterface_vnx_set_config_object_return.hxx>
#include <vnx/ModuleInterface_vnx_stop.hxx>
#include <vnx/ModuleInterface_vnx_stop_return.hxx>
#include <vnx/TopicPtr.hpp>

#include <vnx/vnx.h>


namespace mmx {


const vnx::Hash64 FarmerBase::VNX_TYPE_HASH(0xff732ba14d9d1abull);
const vnx::Hash64 FarmerBase::VNX_CODE_HASH(0x157dc19985ba1f33ull);

FarmerBase::FarmerBase(const std::string& _vnx_name)
	:	Module::Module(_vnx_name)
{
	vnx::read_config(vnx_name + ".input_info", input_info);
	vnx::read_config(vnx_name + ".harvester_timeout", harvester_timeout);
	vnx::read_config(vnx_name + ".node_server", node_server);
	vnx::read_config(vnx_name + ".wallet_server", wallet_server);
	vnx::read_config(vnx_name + ".reward_addr", reward_addr);
	vnx::read_config(vnx_name + ".project_addr", project_addr);
	vnx::read_config(vnx_name + ".devfee_ratio", devfee_ratio);
}

vnx::Hash64 FarmerBase::get_type_hash() const {
	return VNX_TYPE_HASH;
}

std::string FarmerBase::get_type_name() const {
	return "mmx.Farmer";
}

const vnx::TypeCode* FarmerBase::get_type_code() const {
	return mmx::vnx_native_type_code_FarmerBase;
}

void FarmerBase::accept(vnx::Visitor& _visitor) const {
	const vnx::TypeCode* _type_code = mmx::vnx_native_type_code_FarmerBase;
	_visitor.type_begin(*_type_code);
	_visitor.type_field(_type_code->fields[0], 0); vnx::accept(_visitor, input_info);
	_visitor.type_field(_type_code->fields[1], 1); vnx::accept(_visitor, harvester_timeout);
	_visitor.type_field(_type_code->fields[2], 2); vnx::accept(_visitor, node_server);
	_visitor.type_field(_type_code->fields[3], 3); vnx::accept(_visitor, wallet_server);
	_visitor.type_field(_type_code->fields[4], 4); vnx::accept(_visitor, reward_addr);
	_visitor.type_field(_type_code->fields[5], 5); vnx::accept(_visitor, project_addr);
	_visitor.type_field(_type_code->fields[6], 6); vnx::accept(_visitor, devfee_ratio);
	_visitor.type_end(*_type_code);
}

void FarmerBase::write(std::ostream& _out) const {
	_out << "{";
	_out << "\"input_info\": "; vnx::write(_out, input_info);
	_out << ", \"harvester_timeout\": "; vnx::write(_out, harvester_timeout);
	_out << ", \"node_server\": "; vnx::write(_out, node_server);
	_out << ", \"wallet_server\": "; vnx::write(_out, wallet_server);
	_out << ", \"reward_addr\": "; vnx::write(_out, reward_addr);
	_out << ", \"project_addr\": "; vnx::write(_out, project_addr);
	_out << ", \"devfee_ratio\": "; vnx::write(_out, devfee_ratio);
	_out << "}";
}

void FarmerBase::read(std::istream& _in) {
	if(auto _json = vnx::read_json(_in)) {
		from_object(_json->to_object());
	}
}

vnx::Object FarmerBase::to_object() const {
	vnx::Object _object;
	_object["__type"] = "mmx.Farmer";
	_object["input_info"] = input_info;
	_object["harvester_timeout"] = harvester_timeout;
	_object["node_server"] = node_server;
	_object["wallet_server"] = wallet_server;
	_object["reward_addr"] = reward_addr;
	_object["project_addr"] = project_addr;
	_object["devfee_ratio"] = devfee_ratio;
	return _object;
}

void FarmerBase::from_object(const vnx::Object& _object) {
	for(const auto& _entry : _object.field) {
		if(_entry.first == "devfee_ratio") {
			_entry.second.to(devfee_ratio);
		} else if(_entry.first == "harvester_timeout") {
			_entry.second.to(harvester_timeout);
		} else if(_entry.first == "input_info") {
			_entry.second.to(input_info);
		} else if(_entry.first == "node_server") {
			_entry.second.to(node_server);
		} else if(_entry.first == "project_addr") {
			_entry.second.to(project_addr);
		} else if(_entry.first == "reward_addr") {
			_entry.second.to(reward_addr);
		} else if(_entry.first == "wallet_server") {
			_entry.second.to(wallet_server);
		}
	}
}

vnx::Variant FarmerBase::get_field(const std::string& _name) const {
	if(_name == "input_info") {
		return vnx::Variant(input_info);
	}
	if(_name == "harvester_timeout") {
		return vnx::Variant(harvester_timeout);
	}
	if(_name == "node_server") {
		return vnx::Variant(node_server);
	}
	if(_name == "wallet_server") {
		return vnx::Variant(wallet_server);
	}
	if(_name == "reward_addr") {
		return vnx::Variant(reward_addr);
	}
	if(_name == "project_addr") {
		return vnx::Variant(project_addr);
	}
	if(_name == "devfee_ratio") {
		return vnx::Variant(devfee_ratio);
	}
	return vnx::Variant();
}

void FarmerBase::set_field(const std::string& _name, const vnx::Variant& _value) {
	if(_name == "input_info") {
		_value.to(input_info);
	} else if(_name == "harvester_timeout") {
		_value.to(harvester_timeout);
	} else if(_name == "node_server") {
		_value.to(node_server);
	} else if(_name == "wallet_server") {
		_value.to(wallet_server);
	} else if(_name == "reward_addr") {
		_value.to(reward_addr);
	} else if(_name == "project_addr") {
		_value.to(project_addr);
	} else if(_name == "devfee_ratio") {
		_value.to(devfee_ratio);
	}
}

/// \private
std::ostream& operator<<(std::ostream& _out, const FarmerBase& _value) {
	_value.write(_out);
	return _out;
}

/// \private
std::istream& operator>>(std::istream& _in, FarmerBase& _value) {
	_value.read(_in);
	return _in;
}

const vnx::TypeCode* FarmerBase::static_get_type_code() {
	const vnx::TypeCode* type_code = vnx::get_type_code(VNX_TYPE_HASH);
	if(!type_code) {
		type_code = vnx::register_type_code(static_create_type_code());
	}
	return type_code;
}

std::shared_ptr<vnx::TypeCode> FarmerBase::static_create_type_code() {
	auto type_code = std::make_shared<vnx::TypeCode>();
	type_code->name = "mmx.Farmer";
	type_code->type_hash = vnx::Hash64(0xff732ba14d9d1abull);
	type_code->code_hash = vnx::Hash64(0x157dc19985ba1f33ull);
	type_code->is_native = true;
	type_code->native_size = sizeof(::mmx::FarmerBase);
	type_code->methods.resize(14);
	type_code->methods[0] = ::mmx::Farmer_get_farm_info::static_get_type_code();
	type_code->methods[1] = ::mmx::Farmer_get_farmer_keys::static_get_type_code();
	type_code->methods[2] = ::mmx::Farmer_get_mac_addr::static_get_type_code();
	type_code->methods[3] = ::mmx::Farmer_sign_block::static_get_type_code();
	type_code->methods[4] = ::mmx::Farmer_sign_proof::static_get_type_code();
	type_code->methods[5] = ::vnx::ModuleInterface_vnx_get_config::static_get_type_code();
	type_code->methods[6] = ::vnx::ModuleInterface_vnx_get_config_object::static_get_type_code();
	type_code->methods[7] = ::vnx::ModuleInterface_vnx_get_module_info::static_get_type_code();
	type_code->methods[8] = ::vnx::ModuleInterface_vnx_get_type_code::static_get_type_code();
	type_code->methods[9] = ::vnx::ModuleInterface_vnx_restart::static_get_type_code();
	type_code->methods[10] = ::vnx::ModuleInterface_vnx_self_test::static_get_type_code();
	type_code->methods[11] = ::vnx::ModuleInterface_vnx_set_config::static_get_type_code();
	type_code->methods[12] = ::vnx::ModuleInterface_vnx_set_config_object::static_get_type_code();
	type_code->methods[13] = ::vnx::ModuleInterface_vnx_stop::static_get_type_code();
	type_code->fields.resize(7);
	{
		auto& field = type_code->fields[0];
		field.is_extended = true;
		field.name = "input_info";
		field.value = vnx::to_string("harvester.info");
		field.code = {12, 5};
	}
	{
		auto& field = type_code->fields[1];
		field.data_size = 4;
		field.name = "harvester_timeout";
		field.value = vnx::to_string(60);
		field.code = {3};
	}
	{
		auto& field = type_code->fields[2];
		field.is_extended = true;
		field.name = "node_server";
		field.value = vnx::to_string("Node");
		field.code = {32};
	}
	{
		auto& field = type_code->fields[3];
		field.is_extended = true;
		field.name = "wallet_server";
		field.value = vnx::to_string("Wallet");
		field.code = {32};
	}
	{
		auto& field = type_code->fields[4];
		field.is_extended = true;
		field.name = "reward_addr";
		field.code = {33, 11, 32, 1};
	}
	{
		auto& field = type_code->fields[5];
		field.is_extended = true;
		field.name = "project_addr";
		field.code = {33, 11, 32, 1};
	}
	{
		auto& field = type_code->fields[6];
		field.data_size = 8;
		field.name = "devfee_ratio";
		field.value = vnx::to_string(0.05);
		field.code = {10};
	}
	type_code->build();
	return type_code;
}

void FarmerBase::vnx_handle_switch(std::shared_ptr<const vnx::Value> _value) {
	const auto* _type_code = _value->get_type_code();
	while(_type_code) {
		switch(_type_code->type_hash) {
			case 0xa2701372b9137f0eull:
				handle(std::static_pointer_cast<const ::mmx::FarmInfo>(_value));
				return;
			default:
				_type_code = _type_code->super;
		}
	}
	handle(std::static_pointer_cast<const vnx::Value>(_value));
}

std::shared_ptr<vnx::Value> FarmerBase::vnx_call_switch(std::shared_ptr<const vnx::Value> _method, const vnx::request_id_t& _request_id) {
	switch(_method->get_type_hash()) {
		case 0x7e72655f6f215b5aull: {
			auto _args = std::static_pointer_cast<const ::mmx::Farmer_get_farm_info>(_method);
			auto _return_value = ::mmx::Farmer_get_farm_info_return::create();
			_return_value->_ret_0 = get_farm_info();
			return _return_value;
		}
		case 0x784507b4594a776aull: {
			auto _args = std::static_pointer_cast<const ::mmx::Farmer_get_farmer_keys>(_method);
			auto _return_value = ::mmx::Farmer_get_farmer_keys_return::create();
			_return_value->_ret_0 = get_farmer_keys();
			return _return_value;
		}
		case 0xe9ced9f6feb676b3ull: {
			auto _args = std::static_pointer_cast<const ::mmx::Farmer_get_mac_addr>(_method);
			auto _return_value = ::mmx::Farmer_get_mac_addr_return::create();
			_return_value->_ret_0 = get_mac_addr();
			return _return_value;
		}
		case 0x6924b10f345eb316ull: {
			auto _args = std::static_pointer_cast<const ::mmx::Farmer_sign_block>(_method);
			auto _return_value = ::mmx::Farmer_sign_block_return::create();
			_return_value->_ret_0 = sign_block(_args->block, _args->reward_amount);
			return _return_value;
		}
		case 0x7c59d2761514b455ull: {
			auto _args = std::static_pointer_cast<const ::mmx::Farmer_sign_proof>(_method);
			auto _return_value = ::mmx::Farmer_sign_proof_return::create();
			_return_value->_ret_0 = sign_proof(_args->proof);
			return _return_value;
		}
		case 0xbbc7f1a01044d294ull: {
			auto _args = std::static_pointer_cast<const ::vnx::ModuleInterface_vnx_get_config>(_method);
			auto _return_value = ::vnx::ModuleInterface_vnx_get_config_return::create();
			_return_value->_ret_0 = vnx_get_config(_args->name);
			return _return_value;
		}
		case 0x17f58f68bf83abc0ull: {
			auto _args = std::static_pointer_cast<const ::vnx::ModuleInterface_vnx_get_config_object>(_method);
			auto _return_value = ::vnx::ModuleInterface_vnx_get_config_object_return::create();
			_return_value->_ret_0 = vnx_get_config_object();
			return _return_value;
		}
		case 0xf6d82bdf66d034a1ull: {
			auto _args = std::static_pointer_cast<const ::vnx::ModuleInterface_vnx_get_module_info>(_method);
			auto _return_value = ::vnx::ModuleInterface_vnx_get_module_info_return::create();
			_return_value->_ret_0 = vnx_get_module_info();
			return _return_value;
		}
		case 0x305ec4d628960e5dull: {
			auto _args = std::static_pointer_cast<const ::vnx::ModuleInterface_vnx_get_type_code>(_method);
			auto _return_value = ::vnx::ModuleInterface_vnx_get_type_code_return::create();
			_return_value->_ret_0 = vnx_get_type_code();
			return _return_value;
		}
		case 0x9e95dc280cecca1bull: {
			auto _args = std::static_pointer_cast<const ::vnx::ModuleInterface_vnx_restart>(_method);
			auto _return_value = ::vnx::ModuleInterface_vnx_restart_return::create();
			vnx_restart();
			return _return_value;
		}
		case 0x6ce3775b41a42697ull: {
			auto _args = std::static_pointer_cast<const ::vnx::ModuleInterface_vnx_self_test>(_method);
			auto _return_value = ::vnx::ModuleInterface_vnx_self_test_return::create();
			_return_value->_ret_0 = vnx_self_test();
			return _return_value;
		}
		case 0x362aac91373958b7ull: {
			auto _args = std::static_pointer_cast<const ::vnx::ModuleInterface_vnx_set_config>(_method);
			auto _return_value = ::vnx::ModuleInterface_vnx_set_config_return::create();
			vnx_set_config(_args->name, _args->value);
			return _return_value;
		}
		case 0xca30f814f17f322full: {
			auto _args = std::static_pointer_cast<const ::vnx::ModuleInterface_vnx_set_config_object>(_method);
			auto _return_value = ::vnx::ModuleInterface_vnx_set_config_object_return::create();
			vnx_set_config_object(_args->config);
			return _return_value;
		}
		case 0x7ab49ce3d1bfc0d2ull: {
			auto _args = std::static_pointer_cast<const ::vnx::ModuleInterface_vnx_stop>(_method);
			auto _return_value = ::vnx::ModuleInterface_vnx_stop_return::create();
			vnx_stop();
			return _return_value;
		}
	}
	auto _ex = vnx::NoSuchMethod::create();
	_ex->dst_mac = vnx_request ? vnx_request->dst_mac : vnx::Hash64();
	_ex->method = _method->get_type_name();
	return _ex;
}


} // namespace mmx


namespace vnx {

void read(TypeInput& in, ::mmx::FarmerBase& value, const TypeCode* type_code, const uint16_t* code) {
	if(code) {
		switch(code[0]) {
			case CODE_OBJECT:
			case CODE_ALT_OBJECT: {
				Object tmp;
				vnx::read(in, tmp, type_code, code);
				value.from_object(tmp);
				return;
			}
			case CODE_DYNAMIC:
			case CODE_ALT_DYNAMIC:
				vnx::read_dynamic(in, value);
				return;
		}
	}
	if(!type_code) {
		vnx::skip(in, type_code, code);
		return;
	}
	if(code) {
		switch(code[0]) {
			case CODE_STRUCT: type_code = type_code->depends[code[1]]; break;
			case CODE_ALT_STRUCT: type_code = type_code->depends[vnx::flip_bytes(code[1])]; break;
			default: {
				vnx::skip(in, type_code, code);
				return;
			}
		}
	}
	const char* const _buf = in.read(type_code->total_field_size);
	if(type_code->is_matched) {
		if(const auto* const _field = type_code->field_map[1]) {
			vnx::read_value(_buf + _field->offset, value.harvester_timeout, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[6]) {
			vnx::read_value(_buf + _field->offset, value.devfee_ratio, _field->code.data());
		}
	}
	for(const auto* _field : type_code->ext_fields) {
		switch(_field->native_index) {
			case 0: vnx::read(in, value.input_info, type_code, _field->code.data()); break;
			case 2: vnx::read(in, value.node_server, type_code, _field->code.data()); break;
			case 3: vnx::read(in, value.wallet_server, type_code, _field->code.data()); break;
			case 4: vnx::read(in, value.reward_addr, type_code, _field->code.data()); break;
			case 5: vnx::read(in, value.project_addr, type_code, _field->code.data()); break;
			default: vnx::skip(in, type_code, _field->code.data());
		}
	}
}

void write(TypeOutput& out, const ::mmx::FarmerBase& value, const TypeCode* type_code, const uint16_t* code) {
	if(code && code[0] == CODE_OBJECT) {
		vnx::write(out, value.to_object(), nullptr, code);
		return;
	}
	if(!type_code || (code && code[0] == CODE_ANY)) {
		type_code = mmx::vnx_native_type_code_FarmerBase;
		out.write_type_code(type_code);
		vnx::write_class_header<::mmx::FarmerBase>(out);
	}
	else if(code && code[0] == CODE_STRUCT) {
		type_code = type_code->depends[code[1]];
	}
	char* const _buf = out.write(12);
	vnx::write_value(_buf + 0, value.harvester_timeout);
	vnx::write_value(_buf + 4, value.devfee_ratio);
	vnx::write(out, value.input_info, type_code, type_code->fields[0].code.data());
	vnx::write(out, value.node_server, type_code, type_code->fields[2].code.data());
	vnx::write(out, value.wallet_server, type_code, type_code->fields[3].code.data());
	vnx::write(out, value.reward_addr, type_code, type_code->fields[4].code.data());
	vnx::write(out, value.project_addr, type_code, type_code->fields[5].code.data());
}

void read(std::istream& in, ::mmx::FarmerBase& value) {
	value.read(in);
}

void write(std::ostream& out, const ::mmx::FarmerBase& value) {
	value.write(out);
}

void accept(Visitor& visitor, const ::mmx::FarmerBase& value) {
	value.accept(visitor);
}

} // vnx
