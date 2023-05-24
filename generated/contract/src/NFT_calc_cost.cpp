
// AUTO GENERATED by vnxcppcodegen

#include <mmx/contract/package.hxx>
#include <mmx/contract/NFT_calc_cost.hxx>
#include <mmx/ChainParams.hxx>
#include <mmx/contract/NFT_calc_cost_return.hxx>
#include <vnx/Value.h>

#include <vnx/vnx.h>


namespace mmx {
namespace contract {


const vnx::Hash64 NFT_calc_cost::VNX_TYPE_HASH(0x462462234574232ull);
const vnx::Hash64 NFT_calc_cost::VNX_CODE_HASH(0x489ad8c0634ddd17ull);

vnx::Hash64 NFT_calc_cost::get_type_hash() const {
	return VNX_TYPE_HASH;
}

std::string NFT_calc_cost::get_type_name() const {
	return "mmx.contract.NFT.calc_cost";
}

const vnx::TypeCode* NFT_calc_cost::get_type_code() const {
	return mmx::contract::vnx_native_type_code_NFT_calc_cost;
}

std::shared_ptr<NFT_calc_cost> NFT_calc_cost::create() {
	return std::make_shared<NFT_calc_cost>();
}

std::shared_ptr<vnx::Value> NFT_calc_cost::clone() const {
	return std::make_shared<NFT_calc_cost>(*this);
}

void NFT_calc_cost::read(vnx::TypeInput& _in, const vnx::TypeCode* _type_code, const uint16_t* _code) {
	vnx::read(_in, *this, _type_code, _code);
}

void NFT_calc_cost::write(vnx::TypeOutput& _out, const vnx::TypeCode* _type_code, const uint16_t* _code) const {
	vnx::write(_out, *this, _type_code, _code);
}

void NFT_calc_cost::accept(vnx::Visitor& _visitor) const {
	const vnx::TypeCode* _type_code = mmx::contract::vnx_native_type_code_NFT_calc_cost;
	_visitor.type_begin(*_type_code);
	_visitor.type_field(_type_code->fields[0], 0); vnx::accept(_visitor, params);
	_visitor.type_field(_type_code->fields[1], 1); vnx::accept(_visitor, is_read);
	_visitor.type_end(*_type_code);
}

void NFT_calc_cost::write(std::ostream& _out) const {
	_out << "{\"__type\": \"mmx.contract.NFT.calc_cost\"";
	_out << ", \"params\": "; vnx::write(_out, params);
	_out << ", \"is_read\": "; vnx::write(_out, is_read);
	_out << "}";
}

void NFT_calc_cost::read(std::istream& _in) {
	if(auto _json = vnx::read_json(_in)) {
		from_object(_json->to_object());
	}
}

vnx::Object NFT_calc_cost::to_object() const {
	vnx::Object _object;
	_object["__type"] = "mmx.contract.NFT.calc_cost";
	_object["params"] = params;
	_object["is_read"] = is_read;
	return _object;
}

void NFT_calc_cost::from_object(const vnx::Object& _object) {
	for(const auto& _entry : _object.field) {
		if(_entry.first == "is_read") {
			_entry.second.to(is_read);
		} else if(_entry.first == "params") {
			_entry.second.to(params);
		}
	}
}

vnx::Variant NFT_calc_cost::get_field(const std::string& _name) const {
	if(_name == "params") {
		return vnx::Variant(params);
	}
	if(_name == "is_read") {
		return vnx::Variant(is_read);
	}
	return vnx::Variant();
}

void NFT_calc_cost::set_field(const std::string& _name, const vnx::Variant& _value) {
	if(_name == "params") {
		_value.to(params);
	} else if(_name == "is_read") {
		_value.to(is_read);
	}
}

/// \private
std::ostream& operator<<(std::ostream& _out, const NFT_calc_cost& _value) {
	_value.write(_out);
	return _out;
}

/// \private
std::istream& operator>>(std::istream& _in, NFT_calc_cost& _value) {
	_value.read(_in);
	return _in;
}

const vnx::TypeCode* NFT_calc_cost::static_get_type_code() {
	const vnx::TypeCode* type_code = vnx::get_type_code(VNX_TYPE_HASH);
	if(!type_code) {
		type_code = vnx::register_type_code(static_create_type_code());
	}
	return type_code;
}

std::shared_ptr<vnx::TypeCode> NFT_calc_cost::static_create_type_code() {
	auto type_code = std::make_shared<vnx::TypeCode>();
	type_code->name = "mmx.contract.NFT.calc_cost";
	type_code->type_hash = vnx::Hash64(0x462462234574232ull);
	type_code->code_hash = vnx::Hash64(0x489ad8c0634ddd17ull);
	type_code->is_native = true;
	type_code->is_class = true;
	type_code->is_method = true;
	type_code->native_size = sizeof(::mmx::contract::NFT_calc_cost);
	type_code->create_value = []() -> std::shared_ptr<vnx::Value> { return std::make_shared<NFT_calc_cost>(); };
	type_code->is_const = true;
	type_code->return_type = ::mmx::contract::NFT_calc_cost_return::static_get_type_code();
	type_code->fields.resize(2);
	{
		auto& field = type_code->fields[0];
		field.is_extended = true;
		field.name = "params";
		field.code = {16};
	}
	{
		auto& field = type_code->fields[1];
		field.data_size = 1;
		field.name = "is_read";
		field.code = {31};
	}
	type_code->build();
	return type_code;
}


} // namespace mmx
} // namespace contract


namespace vnx {

void read(TypeInput& in, ::mmx::contract::NFT_calc_cost& value, const TypeCode* type_code, const uint16_t* code) {
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
			vnx::read_value(_buf + _field->offset, value.is_read, _field->code.data());
		}
	}
	for(const auto* _field : type_code->ext_fields) {
		switch(_field->native_index) {
			case 0: vnx::read(in, value.params, type_code, _field->code.data()); break;
			default: vnx::skip(in, type_code, _field->code.data());
		}
	}
}

void write(TypeOutput& out, const ::mmx::contract::NFT_calc_cost& value, const TypeCode* type_code, const uint16_t* code) {
	if(code && code[0] == CODE_OBJECT) {
		vnx::write(out, value.to_object(), nullptr, code);
		return;
	}
	if(!type_code || (code && code[0] == CODE_ANY)) {
		type_code = mmx::contract::vnx_native_type_code_NFT_calc_cost;
		out.write_type_code(type_code);
		vnx::write_class_header<::mmx::contract::NFT_calc_cost>(out);
	}
	else if(code && code[0] == CODE_STRUCT) {
		type_code = type_code->depends[code[1]];
	}
	char* const _buf = out.write(1);
	vnx::write_value(_buf + 0, value.is_read);
	vnx::write(out, value.params, type_code, type_code->fields[0].code.data());
}

void read(std::istream& in, ::mmx::contract::NFT_calc_cost& value) {
	value.read(in);
}

void write(std::ostream& out, const ::mmx::contract::NFT_calc_cost& value) {
	value.write(out);
}

void accept(Visitor& visitor, const ::mmx::contract::NFT_calc_cost& value) {
	value.accept(visitor);
}

} // vnx
