
// AUTO GENERATED by vnxcppcodegen

#include <mmx/package.hxx>
#include <mmx/NetworkInfo.hxx>
#include <mmx/hash_t.hpp>
#include <vnx/Value.h>

#include <vnx/vnx.h>


namespace mmx {


const vnx::Hash64 NetworkInfo::VNX_TYPE_HASH(0xd984018819746101ull);
const vnx::Hash64 NetworkInfo::VNX_CODE_HASH(0x5dea3940893dc096ull);

vnx::Hash64 NetworkInfo::get_type_hash() const {
	return VNX_TYPE_HASH;
}

std::string NetworkInfo::get_type_name() const {
	return "mmx.NetworkInfo";
}

const vnx::TypeCode* NetworkInfo::get_type_code() const {
	return mmx::vnx_native_type_code_NetworkInfo;
}

std::shared_ptr<NetworkInfo> NetworkInfo::create() {
	return std::make_shared<NetworkInfo>();
}

std::shared_ptr<vnx::Value> NetworkInfo::clone() const {
	return std::make_shared<NetworkInfo>(*this);
}

void NetworkInfo::read(vnx::TypeInput& _in, const vnx::TypeCode* _type_code, const uint16_t* _code) {
	vnx::read(_in, *this, _type_code, _code);
}

void NetworkInfo::write(vnx::TypeOutput& _out, const vnx::TypeCode* _type_code, const uint16_t* _code) const {
	vnx::write(_out, *this, _type_code, _code);
}

void NetworkInfo::accept(vnx::Visitor& _visitor) const {
	const vnx::TypeCode* _type_code = mmx::vnx_native_type_code_NetworkInfo;
	_visitor.type_begin(*_type_code);
	_visitor.type_field(_type_code->fields[0], 0); vnx::accept(_visitor, is_synced);
	_visitor.type_field(_type_code->fields[1], 1); vnx::accept(_visitor, height);
	_visitor.type_field(_type_code->fields[2], 2); vnx::accept(_visitor, vdf_height);
	_visitor.type_field(_type_code->fields[3], 3); vnx::accept(_visitor, synced_since);
	_visitor.type_field(_type_code->fields[4], 4); vnx::accept(_visitor, time_stamp);
	_visitor.type_field(_type_code->fields[5], 5); vnx::accept(_visitor, time_diff);
	_visitor.type_field(_type_code->fields[6], 6); vnx::accept(_visitor, space_diff);
	_visitor.type_field(_type_code->fields[7], 7); vnx::accept(_visitor, block_reward);
	_visitor.type_field(_type_code->fields[8], 8); vnx::accept(_visitor, total_space);
	_visitor.type_field(_type_code->fields[9], 9); vnx::accept(_visitor, total_supply);
	_visitor.type_field(_type_code->fields[10], 10); vnx::accept(_visitor, address_count);
	_visitor.type_field(_type_code->fields[11], 11); vnx::accept(_visitor, vdf_speed);
	_visitor.type_field(_type_code->fields[12], 12); vnx::accept(_visitor, block_size);
	_visitor.type_field(_type_code->fields[13], 13); vnx::accept(_visitor, average_txfee);
	_visitor.type_field(_type_code->fields[14], 14); vnx::accept(_visitor, genesis_hash);
	_visitor.type_field(_type_code->fields[15], 15); vnx::accept(_visitor, name);
	_visitor.type_end(*_type_code);
}

void NetworkInfo::write(std::ostream& _out) const {
	_out << "{\"__type\": \"mmx.NetworkInfo\"";
	_out << ", \"is_synced\": "; vnx::write(_out, is_synced);
	_out << ", \"height\": "; vnx::write(_out, height);
	_out << ", \"vdf_height\": "; vnx::write(_out, vdf_height);
	_out << ", \"synced_since\": "; vnx::write(_out, synced_since);
	_out << ", \"time_stamp\": "; vnx::write(_out, time_stamp);
	_out << ", \"time_diff\": "; vnx::write(_out, time_diff);
	_out << ", \"space_diff\": "; vnx::write(_out, space_diff);
	_out << ", \"block_reward\": "; vnx::write(_out, block_reward);
	_out << ", \"total_space\": "; vnx::write(_out, total_space);
	_out << ", \"total_supply\": "; vnx::write(_out, total_supply);
	_out << ", \"address_count\": "; vnx::write(_out, address_count);
	_out << ", \"vdf_speed\": "; vnx::write(_out, vdf_speed);
	_out << ", \"block_size\": "; vnx::write(_out, block_size);
	_out << ", \"average_txfee\": "; vnx::write(_out, average_txfee);
	_out << ", \"genesis_hash\": "; vnx::write(_out, genesis_hash);
	_out << ", \"name\": "; vnx::write(_out, name);
	_out << "}";
}

void NetworkInfo::read(std::istream& _in) {
	if(auto _json = vnx::read_json(_in)) {
		from_object(_json->to_object());
	}
}

vnx::Object NetworkInfo::to_object() const {
	vnx::Object _object;
	_object["__type"] = "mmx.NetworkInfo";
	_object["is_synced"] = is_synced;
	_object["height"] = height;
	_object["vdf_height"] = vdf_height;
	_object["synced_since"] = synced_since;
	_object["time_stamp"] = time_stamp;
	_object["time_diff"] = time_diff;
	_object["space_diff"] = space_diff;
	_object["block_reward"] = block_reward;
	_object["total_space"] = total_space;
	_object["total_supply"] = total_supply;
	_object["address_count"] = address_count;
	_object["vdf_speed"] = vdf_speed;
	_object["block_size"] = block_size;
	_object["average_txfee"] = average_txfee;
	_object["genesis_hash"] = genesis_hash;
	_object["name"] = name;
	return _object;
}

void NetworkInfo::from_object(const vnx::Object& _object) {
	for(const auto& _entry : _object.field) {
		if(_entry.first == "address_count") {
			_entry.second.to(address_count);
		} else if(_entry.first == "average_txfee") {
			_entry.second.to(average_txfee);
		} else if(_entry.first == "block_reward") {
			_entry.second.to(block_reward);
		} else if(_entry.first == "block_size") {
			_entry.second.to(block_size);
		} else if(_entry.first == "genesis_hash") {
			_entry.second.to(genesis_hash);
		} else if(_entry.first == "height") {
			_entry.second.to(height);
		} else if(_entry.first == "is_synced") {
			_entry.second.to(is_synced);
		} else if(_entry.first == "name") {
			_entry.second.to(name);
		} else if(_entry.first == "space_diff") {
			_entry.second.to(space_diff);
		} else if(_entry.first == "synced_since") {
			_entry.second.to(synced_since);
		} else if(_entry.first == "time_diff") {
			_entry.second.to(time_diff);
		} else if(_entry.first == "time_stamp") {
			_entry.second.to(time_stamp);
		} else if(_entry.first == "total_space") {
			_entry.second.to(total_space);
		} else if(_entry.first == "total_supply") {
			_entry.second.to(total_supply);
		} else if(_entry.first == "vdf_height") {
			_entry.second.to(vdf_height);
		} else if(_entry.first == "vdf_speed") {
			_entry.second.to(vdf_speed);
		}
	}
}

vnx::Variant NetworkInfo::get_field(const std::string& _name) const {
	if(_name == "is_synced") {
		return vnx::Variant(is_synced);
	}
	if(_name == "height") {
		return vnx::Variant(height);
	}
	if(_name == "vdf_height") {
		return vnx::Variant(vdf_height);
	}
	if(_name == "synced_since") {
		return vnx::Variant(synced_since);
	}
	if(_name == "time_stamp") {
		return vnx::Variant(time_stamp);
	}
	if(_name == "time_diff") {
		return vnx::Variant(time_diff);
	}
	if(_name == "space_diff") {
		return vnx::Variant(space_diff);
	}
	if(_name == "block_reward") {
		return vnx::Variant(block_reward);
	}
	if(_name == "total_space") {
		return vnx::Variant(total_space);
	}
	if(_name == "total_supply") {
		return vnx::Variant(total_supply);
	}
	if(_name == "address_count") {
		return vnx::Variant(address_count);
	}
	if(_name == "vdf_speed") {
		return vnx::Variant(vdf_speed);
	}
	if(_name == "block_size") {
		return vnx::Variant(block_size);
	}
	if(_name == "average_txfee") {
		return vnx::Variant(average_txfee);
	}
	if(_name == "genesis_hash") {
		return vnx::Variant(genesis_hash);
	}
	if(_name == "name") {
		return vnx::Variant(name);
	}
	return vnx::Variant();
}

void NetworkInfo::set_field(const std::string& _name, const vnx::Variant& _value) {
	if(_name == "is_synced") {
		_value.to(is_synced);
	} else if(_name == "height") {
		_value.to(height);
	} else if(_name == "vdf_height") {
		_value.to(vdf_height);
	} else if(_name == "synced_since") {
		_value.to(synced_since);
	} else if(_name == "time_stamp") {
		_value.to(time_stamp);
	} else if(_name == "time_diff") {
		_value.to(time_diff);
	} else if(_name == "space_diff") {
		_value.to(space_diff);
	} else if(_name == "block_reward") {
		_value.to(block_reward);
	} else if(_name == "total_space") {
		_value.to(total_space);
	} else if(_name == "total_supply") {
		_value.to(total_supply);
	} else if(_name == "address_count") {
		_value.to(address_count);
	} else if(_name == "vdf_speed") {
		_value.to(vdf_speed);
	} else if(_name == "block_size") {
		_value.to(block_size);
	} else if(_name == "average_txfee") {
		_value.to(average_txfee);
	} else if(_name == "genesis_hash") {
		_value.to(genesis_hash);
	} else if(_name == "name") {
		_value.to(name);
	}
}

/// \private
std::ostream& operator<<(std::ostream& _out, const NetworkInfo& _value) {
	_value.write(_out);
	return _out;
}

/// \private
std::istream& operator>>(std::istream& _in, NetworkInfo& _value) {
	_value.read(_in);
	return _in;
}

const vnx::TypeCode* NetworkInfo::static_get_type_code() {
	const vnx::TypeCode* type_code = vnx::get_type_code(VNX_TYPE_HASH);
	if(!type_code) {
		type_code = vnx::register_type_code(static_create_type_code());
	}
	return type_code;
}

std::shared_ptr<vnx::TypeCode> NetworkInfo::static_create_type_code() {
	auto type_code = std::make_shared<vnx::TypeCode>();
	type_code->name = "mmx.NetworkInfo";
	type_code->type_hash = vnx::Hash64(0xd984018819746101ull);
	type_code->code_hash = vnx::Hash64(0x5dea3940893dc096ull);
	type_code->is_native = true;
	type_code->is_class = true;
	type_code->native_size = sizeof(::mmx::NetworkInfo);
	type_code->create_value = []() -> std::shared_ptr<vnx::Value> { return std::make_shared<NetworkInfo>(); };
	type_code->fields.resize(16);
	{
		auto& field = type_code->fields[0];
		field.data_size = 1;
		field.name = "is_synced";
		field.code = {31};
	}
	{
		auto& field = type_code->fields[1];
		field.data_size = 4;
		field.name = "height";
		field.code = {3};
	}
	{
		auto& field = type_code->fields[2];
		field.data_size = 4;
		field.name = "vdf_height";
		field.code = {3};
	}
	{
		auto& field = type_code->fields[3];
		field.data_size = 4;
		field.name = "synced_since";
		field.code = {3};
	}
	{
		auto& field = type_code->fields[4];
		field.data_size = 8;
		field.name = "time_stamp";
		field.code = {8};
	}
	{
		auto& field = type_code->fields[5];
		field.data_size = 8;
		field.name = "time_diff";
		field.code = {4};
	}
	{
		auto& field = type_code->fields[6];
		field.data_size = 8;
		field.name = "space_diff";
		field.code = {4};
	}
	{
		auto& field = type_code->fields[7];
		field.data_size = 8;
		field.name = "block_reward";
		field.code = {4};
	}
	{
		auto& field = type_code->fields[8];
		field.data_size = 8;
		field.name = "total_space";
		field.code = {4};
	}
	{
		auto& field = type_code->fields[9];
		field.data_size = 8;
		field.name = "total_supply";
		field.code = {4};
	}
	{
		auto& field = type_code->fields[10];
		field.data_size = 8;
		field.name = "address_count";
		field.code = {4};
	}
	{
		auto& field = type_code->fields[11];
		field.data_size = 8;
		field.name = "vdf_speed";
		field.code = {10};
	}
	{
		auto& field = type_code->fields[12];
		field.data_size = 8;
		field.name = "block_size";
		field.code = {10};
	}
	{
		auto& field = type_code->fields[13];
		field.data_size = 8;
		field.name = "average_txfee";
		field.code = {4};
	}
	{
		auto& field = type_code->fields[14];
		field.is_extended = true;
		field.name = "genesis_hash";
		field.code = {11, 32, 1};
	}
	{
		auto& field = type_code->fields[15];
		field.is_extended = true;
		field.name = "name";
		field.code = {32};
	}
	type_code->build();
	return type_code;
}

std::shared_ptr<vnx::Value> NetworkInfo::vnx_call_switch(std::shared_ptr<const vnx::Value> _method) {
	switch(_method->get_type_hash()) {
	}
	return nullptr;
}


} // namespace mmx


namespace vnx {

void read(TypeInput& in, ::mmx::NetworkInfo& value, const TypeCode* type_code, const uint16_t* code) {
	TypeInput::recursion_t tag(in);
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
	const auto* const _buf = in.read(type_code->total_field_size);
	if(type_code->is_matched) {
		if(const auto* const _field = type_code->field_map[0]) {
			vnx::read_value(_buf + _field->offset, value.is_synced, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[1]) {
			vnx::read_value(_buf + _field->offset, value.height, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[2]) {
			vnx::read_value(_buf + _field->offset, value.vdf_height, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[3]) {
			vnx::read_value(_buf + _field->offset, value.synced_since, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[4]) {
			vnx::read_value(_buf + _field->offset, value.time_stamp, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[5]) {
			vnx::read_value(_buf + _field->offset, value.time_diff, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[6]) {
			vnx::read_value(_buf + _field->offset, value.space_diff, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[7]) {
			vnx::read_value(_buf + _field->offset, value.block_reward, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[8]) {
			vnx::read_value(_buf + _field->offset, value.total_space, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[9]) {
			vnx::read_value(_buf + _field->offset, value.total_supply, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[10]) {
			vnx::read_value(_buf + _field->offset, value.address_count, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[11]) {
			vnx::read_value(_buf + _field->offset, value.vdf_speed, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[12]) {
			vnx::read_value(_buf + _field->offset, value.block_size, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[13]) {
			vnx::read_value(_buf + _field->offset, value.average_txfee, _field->code.data());
		}
	}
	for(const auto* _field : type_code->ext_fields) {
		switch(_field->native_index) {
			case 14: vnx::read(in, value.genesis_hash, type_code, _field->code.data()); break;
			case 15: vnx::read(in, value.name, type_code, _field->code.data()); break;
			default: vnx::skip(in, type_code, _field->code.data());
		}
	}
}

void write(TypeOutput& out, const ::mmx::NetworkInfo& value, const TypeCode* type_code, const uint16_t* code) {
	if(code && code[0] == CODE_OBJECT) {
		vnx::write(out, value.to_object(), nullptr, code);
		return;
	}
	if(!type_code || (code && code[0] == CODE_ANY)) {
		type_code = mmx::vnx_native_type_code_NetworkInfo;
		out.write_type_code(type_code);
		vnx::write_class_header<::mmx::NetworkInfo>(out);
	}
	else if(code && code[0] == CODE_STRUCT) {
		type_code = type_code->depends[code[1]];
	}
	auto* const _buf = out.write(93);
	vnx::write_value(_buf + 0, value.is_synced);
	vnx::write_value(_buf + 1, value.height);
	vnx::write_value(_buf + 5, value.vdf_height);
	vnx::write_value(_buf + 9, value.synced_since);
	vnx::write_value(_buf + 13, value.time_stamp);
	vnx::write_value(_buf + 21, value.time_diff);
	vnx::write_value(_buf + 29, value.space_diff);
	vnx::write_value(_buf + 37, value.block_reward);
	vnx::write_value(_buf + 45, value.total_space);
	vnx::write_value(_buf + 53, value.total_supply);
	vnx::write_value(_buf + 61, value.address_count);
	vnx::write_value(_buf + 69, value.vdf_speed);
	vnx::write_value(_buf + 77, value.block_size);
	vnx::write_value(_buf + 85, value.average_txfee);
	vnx::write(out, value.genesis_hash, type_code, type_code->fields[14].code.data());
	vnx::write(out, value.name, type_code, type_code->fields[15].code.data());
}

void read(std::istream& in, ::mmx::NetworkInfo& value) {
	value.read(in);
}

void write(std::ostream& out, const ::mmx::NetworkInfo& value) {
	value.write(out);
}

void accept(Visitor& visitor, const ::mmx::NetworkInfo& value) {
	value.accept(visitor);
}

} // vnx
