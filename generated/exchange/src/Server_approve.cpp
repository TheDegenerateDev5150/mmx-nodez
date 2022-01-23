
// AUTO GENERATED by vnxcppcodegen

#include <mmx/exchange/package.hxx>
#include <mmx/exchange/Server_approve.hxx>
#include <mmx/Transaction.hxx>
#include <mmx/exchange/Server_approve_return.hxx>
#include <vnx/Value.h>

#include <vnx/vnx.h>


namespace mmx {
namespace exchange {


const vnx::Hash64 Server_approve::VNX_TYPE_HASH(0xe2ce003c827b9aa9ull);
const vnx::Hash64 Server_approve::VNX_CODE_HASH(0x495fe24cef07cf9aull);

vnx::Hash64 Server_approve::get_type_hash() const {
	return VNX_TYPE_HASH;
}

std::string Server_approve::get_type_name() const {
	return "mmx.exchange.Server.approve";
}

const vnx::TypeCode* Server_approve::get_type_code() const {
	return mmx::exchange::vnx_native_type_code_Server_approve;
}

std::shared_ptr<Server_approve> Server_approve::create() {
	return std::make_shared<Server_approve>();
}

std::shared_ptr<vnx::Value> Server_approve::clone() const {
	return std::make_shared<Server_approve>(*this);
}

void Server_approve::read(vnx::TypeInput& _in, const vnx::TypeCode* _type_code, const uint16_t* _code) {
	vnx::read(_in, *this, _type_code, _code);
}

void Server_approve::write(vnx::TypeOutput& _out, const vnx::TypeCode* _type_code, const uint16_t* _code) const {
	vnx::write(_out, *this, _type_code, _code);
}

void Server_approve::accept(vnx::Visitor& _visitor) const {
	const vnx::TypeCode* _type_code = mmx::exchange::vnx_native_type_code_Server_approve;
	_visitor.type_begin(*_type_code);
	_visitor.type_field(_type_code->fields[0], 0); vnx::accept(_visitor, client);
	_visitor.type_field(_type_code->fields[1], 1); vnx::accept(_visitor, tx);
	_visitor.type_end(*_type_code);
}

void Server_approve::write(std::ostream& _out) const {
	_out << "{\"__type\": \"mmx.exchange.Server.approve\"";
	_out << ", \"client\": "; vnx::write(_out, client);
	_out << ", \"tx\": "; vnx::write(_out, tx);
	_out << "}";
}

void Server_approve::read(std::istream& _in) {
	if(auto _json = vnx::read_json(_in)) {
		from_object(_json->to_object());
	}
}

vnx::Object Server_approve::to_object() const {
	vnx::Object _object;
	_object["__type"] = "mmx.exchange.Server.approve";
	_object["client"] = client;
	_object["tx"] = tx;
	return _object;
}

void Server_approve::from_object(const vnx::Object& _object) {
	for(const auto& _entry : _object.field) {
		if(_entry.first == "client") {
			_entry.second.to(client);
		} else if(_entry.first == "tx") {
			_entry.second.to(tx);
		}
	}
}

vnx::Variant Server_approve::get_field(const std::string& _name) const {
	if(_name == "client") {
		return vnx::Variant(client);
	}
	if(_name == "tx") {
		return vnx::Variant(tx);
	}
	return vnx::Variant();
}

void Server_approve::set_field(const std::string& _name, const vnx::Variant& _value) {
	if(_name == "client") {
		_value.to(client);
	} else if(_name == "tx") {
		_value.to(tx);
	} else {
		throw std::logic_error("no such field: '" + _name + "'");
	}
}

/// \private
std::ostream& operator<<(std::ostream& _out, const Server_approve& _value) {
	_value.write(_out);
	return _out;
}

/// \private
std::istream& operator>>(std::istream& _in, Server_approve& _value) {
	_value.read(_in);
	return _in;
}

const vnx::TypeCode* Server_approve::static_get_type_code() {
	const vnx::TypeCode* type_code = vnx::get_type_code(VNX_TYPE_HASH);
	if(!type_code) {
		type_code = vnx::register_type_code(static_create_type_code());
	}
	return type_code;
}

std::shared_ptr<vnx::TypeCode> Server_approve::static_create_type_code() {
	auto type_code = std::make_shared<vnx::TypeCode>();
	type_code->name = "mmx.exchange.Server.approve";
	type_code->type_hash = vnx::Hash64(0xe2ce003c827b9aa9ull);
	type_code->code_hash = vnx::Hash64(0x495fe24cef07cf9aull);
	type_code->is_native = true;
	type_code->is_class = true;
	type_code->is_method = true;
	type_code->native_size = sizeof(::mmx::exchange::Server_approve);
	type_code->create_value = []() -> std::shared_ptr<vnx::Value> { return std::make_shared<Server_approve>(); };
	type_code->return_type = ::mmx::exchange::Server_approve_return::static_get_type_code();
	type_code->fields.resize(2);
	{
		auto& field = type_code->fields[0];
		field.data_size = 8;
		field.name = "client";
		field.code = {4};
	}
	{
		auto& field = type_code->fields[1];
		field.is_extended = true;
		field.name = "tx";
		field.code = {16};
	}
	type_code->build();
	return type_code;
}


} // namespace mmx
} // namespace exchange


namespace vnx {

void read(TypeInput& in, ::mmx::exchange::Server_approve& value, const TypeCode* type_code, const uint16_t* code) {
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
			vnx::read_value(_buf + _field->offset, value.client, _field->code.data());
		}
	}
	for(const auto* _field : type_code->ext_fields) {
		switch(_field->native_index) {
			case 1: vnx::read(in, value.tx, type_code, _field->code.data()); break;
			default: vnx::skip(in, type_code, _field->code.data());
		}
	}
}

void write(TypeOutput& out, const ::mmx::exchange::Server_approve& value, const TypeCode* type_code, const uint16_t* code) {
	if(code && code[0] == CODE_OBJECT) {
		vnx::write(out, value.to_object(), nullptr, code);
		return;
	}
	if(!type_code || (code && code[0] == CODE_ANY)) {
		type_code = mmx::exchange::vnx_native_type_code_Server_approve;
		out.write_type_code(type_code);
		vnx::write_class_header<::mmx::exchange::Server_approve>(out);
	}
	else if(code && code[0] == CODE_STRUCT) {
		type_code = type_code->depends[code[1]];
	}
	char* const _buf = out.write(8);
	vnx::write_value(_buf + 0, value.client);
	vnx::write(out, value.tx, type_code, type_code->fields[1].code.data());
}

void read(std::istream& in, ::mmx::exchange::Server_approve& value) {
	value.read(in);
}

void write(std::ostream& out, const ::mmx::exchange::Server_approve& value) {
	value.write(out);
}

void accept(Visitor& visitor, const ::mmx::exchange::Server_approve& value) {
	value.accept(visitor);
}

} // vnx
