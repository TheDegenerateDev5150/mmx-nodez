
// AUTO GENERATED by vnxcppcodegen

#include <mmx/package.hxx>
#include <mmx/txio_t.hxx>
#include <mmx/ChainParams.hxx>
#include <mmx/addr_t.hpp>
#include <mmx/uint128.hpp>

#include <vnx/vnx.h>


namespace mmx {

const uint32_t txio_t::MAX_MEMO_SIZE;

const vnx::Hash64 txio_t::VNX_TYPE_HASH(0x32adb93b85c82cf4ull);
const vnx::Hash64 txio_t::VNX_CODE_HASH(0x7ddcede672a6e7ddull);

vnx::Hash64 txio_t::get_type_hash() const {
	return VNX_TYPE_HASH;
}

std::string txio_t::get_type_name() const {
	return "mmx.txio_t";
}

const vnx::TypeCode* txio_t::get_type_code() const {
	return mmx::vnx_native_type_code_txio_t;
}

std::shared_ptr<txio_t> txio_t::create() {
	return std::make_shared<txio_t>();
}

std::shared_ptr<txio_t> txio_t::clone() const {
	return std::make_shared<txio_t>(*this);
}

void txio_t::read(vnx::TypeInput& _in, const vnx::TypeCode* _type_code, const uint16_t* _code) {
	vnx::read(_in, *this, _type_code, _code);
}

void txio_t::write(vnx::TypeOutput& _out, const vnx::TypeCode* _type_code, const uint16_t* _code) const {
	vnx::write(_out, *this, _type_code, _code);
}

void txio_t::accept(vnx::Visitor& _visitor) const {
	const vnx::TypeCode* _type_code = mmx::vnx_native_type_code_txio_t;
	_visitor.type_begin(*_type_code);
	_visitor.type_field(_type_code->fields[0], 0); vnx::accept(_visitor, address);
	_visitor.type_field(_type_code->fields[1], 1); vnx::accept(_visitor, contract);
	_visitor.type_field(_type_code->fields[2], 2); vnx::accept(_visitor, amount);
	_visitor.type_field(_type_code->fields[3], 3); vnx::accept(_visitor, memo);
	_visitor.type_end(*_type_code);
}

void txio_t::write(std::ostream& _out) const {
	_out << "{";
	_out << "\"address\": "; vnx::write(_out, address);
	_out << ", \"contract\": "; vnx::write(_out, contract);
	_out << ", \"amount\": "; vnx::write(_out, amount);
	_out << ", \"memo\": "; vnx::write(_out, memo);
	_out << "}";
}

void txio_t::read(std::istream& _in) {
	if(auto _json = vnx::read_json(_in)) {
		from_object(_json->to_object());
	}
}

vnx::Object txio_t::to_object() const {
	vnx::Object _object;
	_object["__type"] = "mmx.txio_t";
	_object["address"] = address;
	_object["contract"] = contract;
	_object["amount"] = amount;
	_object["memo"] = memo;
	return _object;
}

void txio_t::from_object(const vnx::Object& _object) {
	for(const auto& _entry : _object.field) {
		if(_entry.first == "address") {
			_entry.second.to(address);
		} else if(_entry.first == "amount") {
			_entry.second.to(amount);
		} else if(_entry.first == "contract") {
			_entry.second.to(contract);
		} else if(_entry.first == "memo") {
			_entry.second.to(memo);
		}
	}
}

vnx::Variant txio_t::get_field(const std::string& _name) const {
	if(_name == "address") {
		return vnx::Variant(address);
	}
	if(_name == "contract") {
		return vnx::Variant(contract);
	}
	if(_name == "amount") {
		return vnx::Variant(amount);
	}
	if(_name == "memo") {
		return vnx::Variant(memo);
	}
	return vnx::Variant();
}

void txio_t::set_field(const std::string& _name, const vnx::Variant& _value) {
	if(_name == "address") {
		_value.to(address);
	} else if(_name == "contract") {
		_value.to(contract);
	} else if(_name == "amount") {
		_value.to(amount);
	} else if(_name == "memo") {
		_value.to(memo);
	}
}

/// \private
std::ostream& operator<<(std::ostream& _out, const txio_t& _value) {
	_value.write(_out);
	return _out;
}

/// \private
std::istream& operator>>(std::istream& _in, txio_t& _value) {
	_value.read(_in);
	return _in;
}

const vnx::TypeCode* txio_t::static_get_type_code() {
	const vnx::TypeCode* type_code = vnx::get_type_code(VNX_TYPE_HASH);
	if(!type_code) {
		type_code = vnx::register_type_code(static_create_type_code());
	}
	return type_code;
}

std::shared_ptr<vnx::TypeCode> txio_t::static_create_type_code() {
	auto type_code = std::make_shared<vnx::TypeCode>();
	type_code->name = "mmx.txio_t";
	type_code->type_hash = vnx::Hash64(0x32adb93b85c82cf4ull);
	type_code->code_hash = vnx::Hash64(0x7ddcede672a6e7ddull);
	type_code->is_native = true;
	type_code->native_size = sizeof(::mmx::txio_t);
	type_code->create_value = []() -> std::shared_ptr<vnx::Value> { return std::make_shared<vnx::Struct<txio_t>>(); };
	type_code->fields.resize(4);
	{
		auto& field = type_code->fields[0];
		field.is_extended = true;
		field.name = "address";
		field.code = {11, 32, 1};
	}
	{
		auto& field = type_code->fields[1];
		field.is_extended = true;
		field.name = "contract";
		field.code = {11, 32, 1};
	}
	{
		auto& field = type_code->fields[2];
		field.is_extended = true;
		field.name = "amount";
		field.code = {11, 16, 1};
	}
	{
		auto& field = type_code->fields[3];
		field.is_extended = true;
		field.name = "memo";
		field.code = {33, 32};
	}
	type_code->build();
	return type_code;
}


} // namespace mmx


namespace vnx {

void read(TypeInput& in, ::mmx::txio_t& value, const TypeCode* type_code, const uint16_t* code) {
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
			case 0: vnx::read(in, value.address, type_code, _field->code.data()); break;
			case 1: vnx::read(in, value.contract, type_code, _field->code.data()); break;
			case 2: vnx::read(in, value.amount, type_code, _field->code.data()); break;
			case 3: vnx::read(in, value.memo, type_code, _field->code.data()); break;
			default: vnx::skip(in, type_code, _field->code.data());
		}
	}
}

void write(TypeOutput& out, const ::mmx::txio_t& value, const TypeCode* type_code, const uint16_t* code) {
	if(code && code[0] == CODE_OBJECT) {
		vnx::write(out, value.to_object(), nullptr, code);
		return;
	}
	if(!type_code || (code && code[0] == CODE_ANY)) {
		type_code = mmx::vnx_native_type_code_txio_t;
		out.write_type_code(type_code);
		vnx::write_class_header<::mmx::txio_t>(out);
	}
	else if(code && code[0] == CODE_STRUCT) {
		type_code = type_code->depends[code[1]];
	}
	vnx::write(out, value.address, type_code, type_code->fields[0].code.data());
	vnx::write(out, value.contract, type_code, type_code->fields[1].code.data());
	vnx::write(out, value.amount, type_code, type_code->fields[2].code.data());
	vnx::write(out, value.memo, type_code, type_code->fields[3].code.data());
}

void read(std::istream& in, ::mmx::txio_t& value) {
	value.read(in);
}

void write(std::ostream& out, const ::mmx::txio_t& value) {
	value.write(out);
}

void accept(Visitor& visitor, const ::mmx::txio_t& value) {
	value.accept(visitor);
}

bool is_equivalent<::mmx::txio_t>::operator()(const uint16_t* code, const TypeCode* type_code) {
	if(code[0] != CODE_STRUCT || !type_code) {
		return false;
	}
	type_code = type_code->depends[code[1]];
	return type_code->type_hash == ::mmx::txio_t::VNX_TYPE_HASH && type_code->is_equivalent;
}

} // vnx
