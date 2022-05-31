
// AUTO GENERATED by vnxcppcodegen

#include <mmx/contract/package.hxx>
#include <mmx/contract/method_t.hxx>

#include <vnx/vnx.h>


namespace mmx {
namespace contract {


const vnx::Hash64 method_t::VNX_TYPE_HASH(0x1f62512698176a39ull);
const vnx::Hash64 method_t::VNX_CODE_HASH(0xc1e9bd07bc925983ull);

vnx::Hash64 method_t::get_type_hash() const {
	return VNX_TYPE_HASH;
}

std::string method_t::get_type_name() const {
	return "mmx.contract.method_t";
}

const vnx::TypeCode* method_t::get_type_code() const {
	return mmx::contract::vnx_native_type_code_method_t;
}

std::shared_ptr<method_t> method_t::create() {
	return std::make_shared<method_t>();
}

std::shared_ptr<method_t> method_t::clone() const {
	return std::make_shared<method_t>(*this);
}

void method_t::read(vnx::TypeInput& _in, const vnx::TypeCode* _type_code, const uint16_t* _code) {
	vnx::read(_in, *this, _type_code, _code);
}

void method_t::write(vnx::TypeOutput& _out, const vnx::TypeCode* _type_code, const uint16_t* _code) const {
	vnx::write(_out, *this, _type_code, _code);
}

void method_t::accept(vnx::Visitor& _visitor) const {
	const vnx::TypeCode* _type_code = mmx::contract::vnx_native_type_code_method_t;
	_visitor.type_begin(*_type_code);
	_visitor.type_field(_type_code->fields[0], 0); vnx::accept(_visitor, name);
	_visitor.type_field(_type_code->fields[1], 1); vnx::accept(_visitor, info);
	_visitor.type_field(_type_code->fields[2], 2); vnx::accept(_visitor, is_const);
	_visitor.type_field(_type_code->fields[3], 3); vnx::accept(_visitor, is_public);
	_visitor.type_field(_type_code->fields[4], 4); vnx::accept(_visitor, is_payable);
	_visitor.type_field(_type_code->fields[5], 5); vnx::accept(_visitor, entry_point);
	_visitor.type_field(_type_code->fields[6], 6); vnx::accept(_visitor, args);
	_visitor.type_end(*_type_code);
}

void method_t::write(std::ostream& _out) const {
	_out << "{";
	_out << "\"name\": "; vnx::write(_out, name);
	_out << ", \"info\": "; vnx::write(_out, info);
	_out << ", \"is_const\": "; vnx::write(_out, is_const);
	_out << ", \"is_public\": "; vnx::write(_out, is_public);
	_out << ", \"is_payable\": "; vnx::write(_out, is_payable);
	_out << ", \"entry_point\": "; vnx::write(_out, entry_point);
	_out << ", \"args\": "; vnx::write(_out, args);
	_out << "}";
}

void method_t::read(std::istream& _in) {
	if(auto _json = vnx::read_json(_in)) {
		from_object(_json->to_object());
	}
}

vnx::Object method_t::to_object() const {
	vnx::Object _object;
	_object["__type"] = "mmx.contract.method_t";
	_object["name"] = name;
	_object["info"] = info;
	_object["is_const"] = is_const;
	_object["is_public"] = is_public;
	_object["is_payable"] = is_payable;
	_object["entry_point"] = entry_point;
	_object["args"] = args;
	return _object;
}

void method_t::from_object(const vnx::Object& _object) {
	for(const auto& _entry : _object.field) {
		if(_entry.first == "args") {
			_entry.second.to(args);
		} else if(_entry.first == "entry_point") {
			_entry.second.to(entry_point);
		} else if(_entry.first == "info") {
			_entry.second.to(info);
		} else if(_entry.first == "is_const") {
			_entry.second.to(is_const);
		} else if(_entry.first == "is_payable") {
			_entry.second.to(is_payable);
		} else if(_entry.first == "is_public") {
			_entry.second.to(is_public);
		} else if(_entry.first == "name") {
			_entry.second.to(name);
		}
	}
}

vnx::Variant method_t::get_field(const std::string& _name) const {
	if(_name == "name") {
		return vnx::Variant(name);
	}
	if(_name == "info") {
		return vnx::Variant(info);
	}
	if(_name == "is_const") {
		return vnx::Variant(is_const);
	}
	if(_name == "is_public") {
		return vnx::Variant(is_public);
	}
	if(_name == "is_payable") {
		return vnx::Variant(is_payable);
	}
	if(_name == "entry_point") {
		return vnx::Variant(entry_point);
	}
	if(_name == "args") {
		return vnx::Variant(args);
	}
	return vnx::Variant();
}

void method_t::set_field(const std::string& _name, const vnx::Variant& _value) {
	if(_name == "name") {
		_value.to(name);
	} else if(_name == "info") {
		_value.to(info);
	} else if(_name == "is_const") {
		_value.to(is_const);
	} else if(_name == "is_public") {
		_value.to(is_public);
	} else if(_name == "is_payable") {
		_value.to(is_payable);
	} else if(_name == "entry_point") {
		_value.to(entry_point);
	} else if(_name == "args") {
		_value.to(args);
	}
}

/// \private
std::ostream& operator<<(std::ostream& _out, const method_t& _value) {
	_value.write(_out);
	return _out;
}

/// \private
std::istream& operator>>(std::istream& _in, method_t& _value) {
	_value.read(_in);
	return _in;
}

const vnx::TypeCode* method_t::static_get_type_code() {
	const vnx::TypeCode* type_code = vnx::get_type_code(VNX_TYPE_HASH);
	if(!type_code) {
		type_code = vnx::register_type_code(static_create_type_code());
	}
	return type_code;
}

std::shared_ptr<vnx::TypeCode> method_t::static_create_type_code() {
	auto type_code = std::make_shared<vnx::TypeCode>();
	type_code->name = "mmx.contract.method_t";
	type_code->type_hash = vnx::Hash64(0x1f62512698176a39ull);
	type_code->code_hash = vnx::Hash64(0xc1e9bd07bc925983ull);
	type_code->is_native = true;
	type_code->native_size = sizeof(::mmx::contract::method_t);
	type_code->create_value = []() -> std::shared_ptr<vnx::Value> { return std::make_shared<vnx::Struct<method_t>>(); };
	type_code->fields.resize(7);
	{
		auto& field = type_code->fields[0];
		field.is_extended = true;
		field.name = "name";
		field.code = {32};
	}
	{
		auto& field = type_code->fields[1];
		field.is_extended = true;
		field.name = "info";
		field.code = {32};
	}
	{
		auto& field = type_code->fields[2];
		field.data_size = 1;
		field.name = "is_const";
		field.code = {31};
	}
	{
		auto& field = type_code->fields[3];
		field.data_size = 1;
		field.name = "is_public";
		field.code = {31};
	}
	{
		auto& field = type_code->fields[4];
		field.data_size = 1;
		field.name = "is_payable";
		field.code = {31};
	}
	{
		auto& field = type_code->fields[5];
		field.data_size = 4;
		field.name = "entry_point";
		field.code = {3};
	}
	{
		auto& field = type_code->fields[6];
		field.is_extended = true;
		field.name = "args";
		field.code = {12, 32};
	}
	type_code->build();
	return type_code;
}


} // namespace mmx
} // namespace contract


namespace vnx {

void read(TypeInput& in, ::mmx::contract::method_t& value, const TypeCode* type_code, const uint16_t* code) {
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
		if(const auto* const _field = type_code->field_map[2]) {
			vnx::read_value(_buf + _field->offset, value.is_const, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[3]) {
			vnx::read_value(_buf + _field->offset, value.is_public, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[4]) {
			vnx::read_value(_buf + _field->offset, value.is_payable, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[5]) {
			vnx::read_value(_buf + _field->offset, value.entry_point, _field->code.data());
		}
	}
	for(const auto* _field : type_code->ext_fields) {
		switch(_field->native_index) {
			case 0: vnx::read(in, value.name, type_code, _field->code.data()); break;
			case 1: vnx::read(in, value.info, type_code, _field->code.data()); break;
			case 6: vnx::read(in, value.args, type_code, _field->code.data()); break;
			default: vnx::skip(in, type_code, _field->code.data());
		}
	}
}

void write(TypeOutput& out, const ::mmx::contract::method_t& value, const TypeCode* type_code, const uint16_t* code) {
	if(code && code[0] == CODE_OBJECT) {
		vnx::write(out, value.to_object(), nullptr, code);
		return;
	}
	if(!type_code || (code && code[0] == CODE_ANY)) {
		type_code = mmx::contract::vnx_native_type_code_method_t;
		out.write_type_code(type_code);
		vnx::write_class_header<::mmx::contract::method_t>(out);
	}
	else if(code && code[0] == CODE_STRUCT) {
		type_code = type_code->depends[code[1]];
	}
	char* const _buf = out.write(7);
	vnx::write_value(_buf + 0, value.is_const);
	vnx::write_value(_buf + 1, value.is_public);
	vnx::write_value(_buf + 2, value.is_payable);
	vnx::write_value(_buf + 3, value.entry_point);
	vnx::write(out, value.name, type_code, type_code->fields[0].code.data());
	vnx::write(out, value.info, type_code, type_code->fields[1].code.data());
	vnx::write(out, value.args, type_code, type_code->fields[6].code.data());
}

void read(std::istream& in, ::mmx::contract::method_t& value) {
	value.read(in);
}

void write(std::ostream& out, const ::mmx::contract::method_t& value) {
	value.write(out);
}

void accept(Visitor& visitor, const ::mmx::contract::method_t& value) {
	value.accept(visitor);
}

bool is_equivalent<::mmx::contract::method_t>::operator()(const uint16_t* code, const TypeCode* type_code) {
	if(code[0] != CODE_STRUCT || !type_code) {
		return false;
	}
	type_code = type_code->depends[code[1]];
	return type_code->type_hash == ::mmx::contract::method_t::VNX_TYPE_HASH && type_code->is_equivalent;
}

} // vnx
