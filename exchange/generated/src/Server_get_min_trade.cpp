
// AUTO GENERATED by vnxcppcodegen

#include <mmx/exchange/package.hxx>
#include <mmx/exchange/Server_get_min_trade.hxx>
#include <mmx/exchange/Server_get_min_trade_return.hxx>
#include <mmx/exchange/trade_pair_t.hxx>
#include <vnx/Value.h>

#include <vnx/vnx.h>


namespace mmx {
namespace exchange {


const vnx::Hash64 Server_get_min_trade::VNX_TYPE_HASH(0xda60d78d7e48e2abull);
const vnx::Hash64 Server_get_min_trade::VNX_CODE_HASH(0x221cf17d2841b5b8ull);

vnx::Hash64 Server_get_min_trade::get_type_hash() const {
	return VNX_TYPE_HASH;
}

std::string Server_get_min_trade::get_type_name() const {
	return "mmx.exchange.Server.get_min_trade";
}

const vnx::TypeCode* Server_get_min_trade::get_type_code() const {
	return mmx::exchange::vnx_native_type_code_Server_get_min_trade;
}

std::shared_ptr<Server_get_min_trade> Server_get_min_trade::create() {
	return std::make_shared<Server_get_min_trade>();
}

std::shared_ptr<vnx::Value> Server_get_min_trade::clone() const {
	return std::make_shared<Server_get_min_trade>(*this);
}

void Server_get_min_trade::read(vnx::TypeInput& _in, const vnx::TypeCode* _type_code, const uint16_t* _code) {
	vnx::read(_in, *this, _type_code, _code);
}

void Server_get_min_trade::write(vnx::TypeOutput& _out, const vnx::TypeCode* _type_code, const uint16_t* _code) const {
	vnx::write(_out, *this, _type_code, _code);
}

void Server_get_min_trade::accept(vnx::Visitor& _visitor) const {
	const vnx::TypeCode* _type_code = mmx::exchange::vnx_native_type_code_Server_get_min_trade;
	_visitor.type_begin(*_type_code);
	_visitor.type_field(_type_code->fields[0], 0); vnx::accept(_visitor, pair);
	_visitor.type_end(*_type_code);
}

void Server_get_min_trade::write(std::ostream& _out) const {
	_out << "{\"__type\": \"mmx.exchange.Server.get_min_trade\"";
	_out << ", \"pair\": "; vnx::write(_out, pair);
	_out << "}";
}

void Server_get_min_trade::read(std::istream& _in) {
	if(auto _json = vnx::read_json(_in)) {
		from_object(_json->to_object());
	}
}

vnx::Object Server_get_min_trade::to_object() const {
	vnx::Object _object;
	_object["__type"] = "mmx.exchange.Server.get_min_trade";
	_object["pair"] = pair;
	return _object;
}

void Server_get_min_trade::from_object(const vnx::Object& _object) {
	for(const auto& _entry : _object.field) {
		if(_entry.first == "pair") {
			_entry.second.to(pair);
		}
	}
}

vnx::Variant Server_get_min_trade::get_field(const std::string& _name) const {
	if(_name == "pair") {
		return vnx::Variant(pair);
	}
	return vnx::Variant();
}

void Server_get_min_trade::set_field(const std::string& _name, const vnx::Variant& _value) {
	if(_name == "pair") {
		_value.to(pair);
	}
}

/// \private
std::ostream& operator<<(std::ostream& _out, const Server_get_min_trade& _value) {
	_value.write(_out);
	return _out;
}

/// \private
std::istream& operator>>(std::istream& _in, Server_get_min_trade& _value) {
	_value.read(_in);
	return _in;
}

const vnx::TypeCode* Server_get_min_trade::static_get_type_code() {
	const vnx::TypeCode* type_code = vnx::get_type_code(VNX_TYPE_HASH);
	if(!type_code) {
		type_code = vnx::register_type_code(static_create_type_code());
	}
	return type_code;
}

std::shared_ptr<vnx::TypeCode> Server_get_min_trade::static_create_type_code() {
	auto type_code = std::make_shared<vnx::TypeCode>();
	type_code->name = "mmx.exchange.Server.get_min_trade";
	type_code->type_hash = vnx::Hash64(0xda60d78d7e48e2abull);
	type_code->code_hash = vnx::Hash64(0x221cf17d2841b5b8ull);
	type_code->is_native = true;
	type_code->is_class = true;
	type_code->is_method = true;
	type_code->native_size = sizeof(::mmx::exchange::Server_get_min_trade);
	type_code->create_value = []() -> std::shared_ptr<vnx::Value> { return std::make_shared<Server_get_min_trade>(); };
	type_code->depends.resize(1);
	type_code->depends[0] = ::mmx::exchange::trade_pair_t::static_get_type_code();
	type_code->is_const = true;
	type_code->return_type = ::mmx::exchange::Server_get_min_trade_return::static_get_type_code();
	type_code->fields.resize(1);
	{
		auto& field = type_code->fields[0];
		field.is_extended = true;
		field.name = "pair";
		field.code = {19, 0};
	}
	type_code->permission = "mmx.permission_e.PUBLIC";
	type_code->build();
	return type_code;
}


} // namespace mmx
} // namespace exchange


namespace vnx {

void read(TypeInput& in, ::mmx::exchange::Server_get_min_trade& value, const TypeCode* type_code, const uint16_t* code) {
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
	in.read(type_code->total_field_size);
	if(type_code->is_matched) {
	}
	for(const auto* _field : type_code->ext_fields) {
		switch(_field->native_index) {
			case 0: vnx::read(in, value.pair, type_code, _field->code.data()); break;
			default: vnx::skip(in, type_code, _field->code.data());
		}
	}
}

void write(TypeOutput& out, const ::mmx::exchange::Server_get_min_trade& value, const TypeCode* type_code, const uint16_t* code) {
	if(code && code[0] == CODE_OBJECT) {
		vnx::write(out, value.to_object(), nullptr, code);
		return;
	}
	if(!type_code || (code && code[0] == CODE_ANY)) {
		type_code = mmx::exchange::vnx_native_type_code_Server_get_min_trade;
		out.write_type_code(type_code);
		vnx::write_class_header<::mmx::exchange::Server_get_min_trade>(out);
	}
	else if(code && code[0] == CODE_STRUCT) {
		type_code = type_code->depends[code[1]];
	}
	vnx::write(out, value.pair, type_code, type_code->fields[0].code.data());
}

void read(std::istream& in, ::mmx::exchange::Server_get_min_trade& value) {
	value.read(in);
}

void write(std::ostream& out, const ::mmx::exchange::Server_get_min_trade& value) {
	value.write(out);
}

void accept(Visitor& visitor, const ::mmx::exchange::Server_get_min_trade& value) {
	value.accept(visitor);
}

} // vnx
