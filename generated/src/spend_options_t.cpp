
// AUTO GENERATED by vnxcppcodegen

#include <mmx/package.hxx>
#include <mmx/spend_options_t.hxx>
#include <mmx/Contract.hxx>
#include <mmx/addr_t.hpp>
#include <mmx/uint128.hpp>

#include <vnx/vnx.h>


namespace mmx {


const vnx::Hash64 spend_options_t::VNX_TYPE_HASH(0x37f7c6d377362e95ull);
const vnx::Hash64 spend_options_t::VNX_CODE_HASH(0x2b7b974bc11679b6ull);

vnx::Hash64 spend_options_t::get_type_hash() const {
	return VNX_TYPE_HASH;
}

std::string spend_options_t::get_type_name() const {
	return "mmx.spend_options_t";
}

const vnx::TypeCode* spend_options_t::get_type_code() const {
	return mmx::vnx_native_type_code_spend_options_t;
}

std::shared_ptr<spend_options_t> spend_options_t::create() {
	return std::make_shared<spend_options_t>();
}

std::shared_ptr<spend_options_t> spend_options_t::clone() const {
	return std::make_shared<spend_options_t>(*this);
}

void spend_options_t::read(vnx::TypeInput& _in, const vnx::TypeCode* _type_code, const uint16_t* _code) {
	vnx::read(_in, *this, _type_code, _code);
}

void spend_options_t::write(vnx::TypeOutput& _out, const vnx::TypeCode* _type_code, const uint16_t* _code) const {
	vnx::write(_out, *this, _type_code, _code);
}

void spend_options_t::accept(vnx::Visitor& _visitor) const {
	const vnx::TypeCode* _type_code = mmx::vnx_native_type_code_spend_options_t;
	_visitor.type_begin(*_type_code);
	_visitor.type_field(_type_code->fields[0], 0); vnx::accept(_visitor, min_confirm);
	_visitor.type_field(_type_code->fields[1], 1); vnx::accept(_visitor, fee_ratio);
	_visitor.type_field(_type_code->fields[2], 2); vnx::accept(_visitor, extra_fee);
	_visitor.type_field(_type_code->fields[3], 3); vnx::accept(_visitor, user);
	_visitor.type_field(_type_code->fields[4], 4); vnx::accept(_visitor, sender);
	_visitor.type_field(_type_code->fields[5], 5); vnx::accept(_visitor, owner_map);
	_visitor.type_field(_type_code->fields[6], 6); vnx::accept(_visitor, contract_map);
	_visitor.type_field(_type_code->fields[7], 7); vnx::accept(_visitor, budget_map);
	_visitor.type_end(*_type_code);
}

void spend_options_t::write(std::ostream& _out) const {
	_out << "{";
	_out << "\"min_confirm\": "; vnx::write(_out, min_confirm);
	_out << ", \"fee_ratio\": "; vnx::write(_out, fee_ratio);
	_out << ", \"extra_fee\": "; vnx::write(_out, extra_fee);
	_out << ", \"user\": "; vnx::write(_out, user);
	_out << ", \"sender\": "; vnx::write(_out, sender);
	_out << ", \"owner_map\": "; vnx::write(_out, owner_map);
	_out << ", \"contract_map\": "; vnx::write(_out, contract_map);
	_out << ", \"budget_map\": "; vnx::write(_out, budget_map);
	_out << "}";
}

void spend_options_t::read(std::istream& _in) {
	if(auto _json = vnx::read_json(_in)) {
		from_object(_json->to_object());
	}
}

vnx::Object spend_options_t::to_object() const {
	vnx::Object _object;
	_object["__type"] = "mmx.spend_options_t";
	_object["min_confirm"] = min_confirm;
	_object["fee_ratio"] = fee_ratio;
	_object["extra_fee"] = extra_fee;
	_object["user"] = user;
	_object["sender"] = sender;
	_object["owner_map"] = owner_map;
	_object["contract_map"] = contract_map;
	_object["budget_map"] = budget_map;
	return _object;
}

void spend_options_t::from_object(const vnx::Object& _object) {
	for(const auto& _entry : _object.field) {
		if(_entry.first == "budget_map") {
			_entry.second.to(budget_map);
		} else if(_entry.first == "contract_map") {
			_entry.second.to(contract_map);
		} else if(_entry.first == "extra_fee") {
			_entry.second.to(extra_fee);
		} else if(_entry.first == "fee_ratio") {
			_entry.second.to(fee_ratio);
		} else if(_entry.first == "min_confirm") {
			_entry.second.to(min_confirm);
		} else if(_entry.first == "owner_map") {
			_entry.second.to(owner_map);
		} else if(_entry.first == "sender") {
			_entry.second.to(sender);
		} else if(_entry.first == "user") {
			_entry.second.to(user);
		}
	}
}

vnx::Variant spend_options_t::get_field(const std::string& _name) const {
	if(_name == "min_confirm") {
		return vnx::Variant(min_confirm);
	}
	if(_name == "fee_ratio") {
		return vnx::Variant(fee_ratio);
	}
	if(_name == "extra_fee") {
		return vnx::Variant(extra_fee);
	}
	if(_name == "user") {
		return vnx::Variant(user);
	}
	if(_name == "sender") {
		return vnx::Variant(sender);
	}
	if(_name == "owner_map") {
		return vnx::Variant(owner_map);
	}
	if(_name == "contract_map") {
		return vnx::Variant(contract_map);
	}
	if(_name == "budget_map") {
		return vnx::Variant(budget_map);
	}
	return vnx::Variant();
}

void spend_options_t::set_field(const std::string& _name, const vnx::Variant& _value) {
	if(_name == "min_confirm") {
		_value.to(min_confirm);
	} else if(_name == "fee_ratio") {
		_value.to(fee_ratio);
	} else if(_name == "extra_fee") {
		_value.to(extra_fee);
	} else if(_name == "user") {
		_value.to(user);
	} else if(_name == "sender") {
		_value.to(sender);
	} else if(_name == "owner_map") {
		_value.to(owner_map);
	} else if(_name == "contract_map") {
		_value.to(contract_map);
	} else if(_name == "budget_map") {
		_value.to(budget_map);
	}
}

/// \private
std::ostream& operator<<(std::ostream& _out, const spend_options_t& _value) {
	_value.write(_out);
	return _out;
}

/// \private
std::istream& operator>>(std::istream& _in, spend_options_t& _value) {
	_value.read(_in);
	return _in;
}

const vnx::TypeCode* spend_options_t::static_get_type_code() {
	const vnx::TypeCode* type_code = vnx::get_type_code(VNX_TYPE_HASH);
	if(!type_code) {
		type_code = vnx::register_type_code(static_create_type_code());
	}
	return type_code;
}

std::shared_ptr<vnx::TypeCode> spend_options_t::static_create_type_code() {
	auto type_code = std::make_shared<vnx::TypeCode>();
	type_code->name = "mmx.spend_options_t";
	type_code->type_hash = vnx::Hash64(0x37f7c6d377362e95ull);
	type_code->code_hash = vnx::Hash64(0x2b7b974bc11679b6ull);
	type_code->is_native = true;
	type_code->native_size = sizeof(::mmx::spend_options_t);
	type_code->create_value = []() -> std::shared_ptr<vnx::Value> { return std::make_shared<vnx::Struct<spend_options_t>>(); };
	type_code->fields.resize(8);
	{
		auto& field = type_code->fields[0];
		field.data_size = 4;
		field.name = "min_confirm";
		field.value = vnx::to_string(1);
		field.code = {3};
	}
	{
		auto& field = type_code->fields[1];
		field.data_size = 4;
		field.name = "fee_ratio";
		field.value = vnx::to_string(1024);
		field.code = {3};
	}
	{
		auto& field = type_code->fields[2];
		field.data_size = 8;
		field.name = "extra_fee";
		field.code = {4};
	}
	{
		auto& field = type_code->fields[3];
		field.is_extended = true;
		field.name = "user";
		field.code = {33, 11, 32, 1};
	}
	{
		auto& field = type_code->fields[4];
		field.is_extended = true;
		field.name = "sender";
		field.code = {33, 11, 32, 1};
	}
	{
		auto& field = type_code->fields[5];
		field.is_extended = true;
		field.name = "owner_map";
		field.code = {13, 5, 11, 32, 1, 11, 32, 1};
	}
	{
		auto& field = type_code->fields[6];
		field.is_extended = true;
		field.name = "contract_map";
		field.code = {13, 5, 11, 32, 1, 16};
	}
	{
		auto& field = type_code->fields[7];
		field.is_extended = true;
		field.name = "budget_map";
		field.code = {33, 13, 5, 11, 32, 1, 11, 16, 1};
	}
	type_code->build();
	return type_code;
}


} // namespace mmx


namespace vnx {

void read(TypeInput& in, ::mmx::spend_options_t& value, const TypeCode* type_code, const uint16_t* code) {
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
		if(const auto* const _field = type_code->field_map[0]) {
			vnx::read_value(_buf + _field->offset, value.min_confirm, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[1]) {
			vnx::read_value(_buf + _field->offset, value.fee_ratio, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[2]) {
			vnx::read_value(_buf + _field->offset, value.extra_fee, _field->code.data());
		}
	}
	for(const auto* _field : type_code->ext_fields) {
		switch(_field->native_index) {
			case 3: vnx::read(in, value.user, type_code, _field->code.data()); break;
			case 4: vnx::read(in, value.sender, type_code, _field->code.data()); break;
			case 5: vnx::read(in, value.owner_map, type_code, _field->code.data()); break;
			case 6: vnx::read(in, value.contract_map, type_code, _field->code.data()); break;
			case 7: vnx::read(in, value.budget_map, type_code, _field->code.data()); break;
			default: vnx::skip(in, type_code, _field->code.data());
		}
	}
}

void write(TypeOutput& out, const ::mmx::spend_options_t& value, const TypeCode* type_code, const uint16_t* code) {
	if(code && code[0] == CODE_OBJECT) {
		vnx::write(out, value.to_object(), nullptr, code);
		return;
	}
	if(!type_code || (code && code[0] == CODE_ANY)) {
		type_code = mmx::vnx_native_type_code_spend_options_t;
		out.write_type_code(type_code);
		vnx::write_class_header<::mmx::spend_options_t>(out);
	}
	else if(code && code[0] == CODE_STRUCT) {
		type_code = type_code->depends[code[1]];
	}
	char* const _buf = out.write(16);
	vnx::write_value(_buf + 0, value.min_confirm);
	vnx::write_value(_buf + 4, value.fee_ratio);
	vnx::write_value(_buf + 8, value.extra_fee);
	vnx::write(out, value.user, type_code, type_code->fields[3].code.data());
	vnx::write(out, value.sender, type_code, type_code->fields[4].code.data());
	vnx::write(out, value.owner_map, type_code, type_code->fields[5].code.data());
	vnx::write(out, value.contract_map, type_code, type_code->fields[6].code.data());
	vnx::write(out, value.budget_map, type_code, type_code->fields[7].code.data());
}

void read(std::istream& in, ::mmx::spend_options_t& value) {
	value.read(in);
}

void write(std::ostream& out, const ::mmx::spend_options_t& value) {
	value.write(out);
}

void accept(Visitor& visitor, const ::mmx::spend_options_t& value) {
	value.accept(visitor);
}

bool is_equivalent<::mmx::spend_options_t>::operator()(const uint16_t* code, const TypeCode* type_code) {
	if(code[0] != CODE_STRUCT || !type_code) {
		return false;
	}
	type_code = type_code->depends[code[1]];
	return type_code->type_hash == ::mmx::spend_options_t::VNX_TYPE_HASH && type_code->is_equivalent;
}

} // vnx
