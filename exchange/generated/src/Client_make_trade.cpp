
// AUTO GENERATED by vnxcppcodegen

#include <mmx/exchange/package.hxx>
#include <mmx/exchange/Client_make_trade.hxx>
#include <mmx/exchange/Client_make_trade_return.hxx>
#include <mmx/exchange/trade_pair_t.hxx>
#include <vnx/Value.h>

#include <vnx/vnx.h>


namespace mmx {
namespace exchange {


const vnx::Hash64 Client_make_trade::VNX_TYPE_HASH(0x10fff803f7c32a54ull);
const vnx::Hash64 Client_make_trade::VNX_CODE_HASH(0xe818e369d0f9f62dull);

vnx::Hash64 Client_make_trade::get_type_hash() const {
	return VNX_TYPE_HASH;
}

std::string Client_make_trade::get_type_name() const {
	return "mmx.exchange.Client.make_trade";
}

const vnx::TypeCode* Client_make_trade::get_type_code() const {
	return mmx::exchange::vnx_native_type_code_Client_make_trade;
}

std::shared_ptr<Client_make_trade> Client_make_trade::create() {
	return std::make_shared<Client_make_trade>();
}

std::shared_ptr<vnx::Value> Client_make_trade::clone() const {
	return std::make_shared<Client_make_trade>(*this);
}

void Client_make_trade::read(vnx::TypeInput& _in, const vnx::TypeCode* _type_code, const uint16_t* _code) {
	vnx::read(_in, *this, _type_code, _code);
}

void Client_make_trade::write(vnx::TypeOutput& _out, const vnx::TypeCode* _type_code, const uint16_t* _code) const {
	vnx::write(_out, *this, _type_code, _code);
}

void Client_make_trade::accept(vnx::Visitor& _visitor) const {
	const vnx::TypeCode* _type_code = mmx::exchange::vnx_native_type_code_Client_make_trade;
	_visitor.type_begin(*_type_code);
	_visitor.type_field(_type_code->fields[0], 0); vnx::accept(_visitor, wallet);
	_visitor.type_field(_type_code->fields[1], 1); vnx::accept(_visitor, pair);
	_visitor.type_field(_type_code->fields[2], 2); vnx::accept(_visitor, bid);
	_visitor.type_field(_type_code->fields[3], 3); vnx::accept(_visitor, ask);
	_visitor.type_end(*_type_code);
}

void Client_make_trade::write(std::ostream& _out) const {
	_out << "{\"__type\": \"mmx.exchange.Client.make_trade\"";
	_out << ", \"wallet\": "; vnx::write(_out, wallet);
	_out << ", \"pair\": "; vnx::write(_out, pair);
	_out << ", \"bid\": "; vnx::write(_out, bid);
	_out << ", \"ask\": "; vnx::write(_out, ask);
	_out << "}";
}

void Client_make_trade::read(std::istream& _in) {
	if(auto _json = vnx::read_json(_in)) {
		from_object(_json->to_object());
	}
}

vnx::Object Client_make_trade::to_object() const {
	vnx::Object _object;
	_object["__type"] = "mmx.exchange.Client.make_trade";
	_object["wallet"] = wallet;
	_object["pair"] = pair;
	_object["bid"] = bid;
	_object["ask"] = ask;
	return _object;
}

void Client_make_trade::from_object(const vnx::Object& _object) {
	for(const auto& _entry : _object.field) {
		if(_entry.first == "ask") {
			_entry.second.to(ask);
		} else if(_entry.first == "bid") {
			_entry.second.to(bid);
		} else if(_entry.first == "pair") {
			_entry.second.to(pair);
		} else if(_entry.first == "wallet") {
			_entry.second.to(wallet);
		}
	}
}

vnx::Variant Client_make_trade::get_field(const std::string& _name) const {
	if(_name == "wallet") {
		return vnx::Variant(wallet);
	}
	if(_name == "pair") {
		return vnx::Variant(pair);
	}
	if(_name == "bid") {
		return vnx::Variant(bid);
	}
	if(_name == "ask") {
		return vnx::Variant(ask);
	}
	return vnx::Variant();
}

void Client_make_trade::set_field(const std::string& _name, const vnx::Variant& _value) {
	if(_name == "wallet") {
		_value.to(wallet);
	} else if(_name == "pair") {
		_value.to(pair);
	} else if(_name == "bid") {
		_value.to(bid);
	} else if(_name == "ask") {
		_value.to(ask);
	}
}

/// \private
std::ostream& operator<<(std::ostream& _out, const Client_make_trade& _value) {
	_value.write(_out);
	return _out;
}

/// \private
std::istream& operator>>(std::istream& _in, Client_make_trade& _value) {
	_value.read(_in);
	return _in;
}

const vnx::TypeCode* Client_make_trade::static_get_type_code() {
	const vnx::TypeCode* type_code = vnx::get_type_code(VNX_TYPE_HASH);
	if(!type_code) {
		type_code = vnx::register_type_code(static_create_type_code());
	}
	return type_code;
}

std::shared_ptr<vnx::TypeCode> Client_make_trade::static_create_type_code() {
	auto type_code = std::make_shared<vnx::TypeCode>();
	type_code->name = "mmx.exchange.Client.make_trade";
	type_code->type_hash = vnx::Hash64(0x10fff803f7c32a54ull);
	type_code->code_hash = vnx::Hash64(0xe818e369d0f9f62dull);
	type_code->is_native = true;
	type_code->is_class = true;
	type_code->is_method = true;
	type_code->native_size = sizeof(::mmx::exchange::Client_make_trade);
	type_code->create_value = []() -> std::shared_ptr<vnx::Value> { return std::make_shared<Client_make_trade>(); };
	type_code->depends.resize(1);
	type_code->depends[0] = ::mmx::exchange::trade_pair_t::static_get_type_code();
	type_code->is_const = true;
	type_code->return_type = ::mmx::exchange::Client_make_trade_return::static_get_type_code();
	type_code->fields.resize(4);
	{
		auto& field = type_code->fields[0];
		field.data_size = 4;
		field.name = "wallet";
		field.code = {3};
	}
	{
		auto& field = type_code->fields[1];
		field.is_extended = true;
		field.name = "pair";
		field.code = {19, 0};
	}
	{
		auto& field = type_code->fields[2];
		field.data_size = 8;
		field.name = "bid";
		field.code = {4};
	}
	{
		auto& field = type_code->fields[3];
		field.is_extended = true;
		field.name = "ask";
		field.code = {33, 4};
	}
	type_code->build();
	return type_code;
}


} // namespace mmx
} // namespace exchange


namespace vnx {

void read(TypeInput& in, ::mmx::exchange::Client_make_trade& value, const TypeCode* type_code, const uint16_t* code) {
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
			vnx::read_value(_buf + _field->offset, value.wallet, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[2]) {
			vnx::read_value(_buf + _field->offset, value.bid, _field->code.data());
		}
	}
	for(const auto* _field : type_code->ext_fields) {
		switch(_field->native_index) {
			case 1: vnx::read(in, value.pair, type_code, _field->code.data()); break;
			case 3: vnx::read(in, value.ask, type_code, _field->code.data()); break;
			default: vnx::skip(in, type_code, _field->code.data());
		}
	}
}

void write(TypeOutput& out, const ::mmx::exchange::Client_make_trade& value, const TypeCode* type_code, const uint16_t* code) {
	if(code && code[0] == CODE_OBJECT) {
		vnx::write(out, value.to_object(), nullptr, code);
		return;
	}
	if(!type_code || (code && code[0] == CODE_ANY)) {
		type_code = mmx::exchange::vnx_native_type_code_Client_make_trade;
		out.write_type_code(type_code);
		vnx::write_class_header<::mmx::exchange::Client_make_trade>(out);
	}
	else if(code && code[0] == CODE_STRUCT) {
		type_code = type_code->depends[code[1]];
	}
	char* const _buf = out.write(12);
	vnx::write_value(_buf + 0, value.wallet);
	vnx::write_value(_buf + 4, value.bid);
	vnx::write(out, value.pair, type_code, type_code->fields[1].code.data());
	vnx::write(out, value.ask, type_code, type_code->fields[3].code.data());
}

void read(std::istream& in, ::mmx::exchange::Client_make_trade& value) {
	value.read(in);
}

void write(std::ostream& out, const ::mmx::exchange::Client_make_trade& value) {
	value.write(out);
}

void accept(Visitor& visitor, const ::mmx::exchange::Client_make_trade& value) {
	value.accept(visitor);
}

} // vnx
