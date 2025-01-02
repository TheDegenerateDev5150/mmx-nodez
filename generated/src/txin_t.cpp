
// AUTO GENERATED by vnxcppcodegen

#include <mmx/package.hxx>
#include <mmx/txin_t.hxx>
#include <mmx/txio_t.hxx>

#include <vnx/vnx.h>


namespace mmx {

const uint8_t txin_t::IS_EXEC;
const uint16_t txin_t::NO_SOLUTION;

const vnx::Hash64 txin_t::VNX_TYPE_HASH(0xda6587114a2413full);
const vnx::Hash64 txin_t::VNX_CODE_HASH(0xf995f5e67a956c4eull);

vnx::Hash64 txin_t::get_type_hash() const {
	return VNX_TYPE_HASH;
}

std::string txin_t::get_type_name() const {
	return "mmx.txin_t";
}

const vnx::TypeCode* txin_t::get_type_code() const {
	return mmx::vnx_native_type_code_txin_t;
}

std::shared_ptr<txin_t> txin_t::create() {
	return std::make_shared<txin_t>();
}

std::shared_ptr<txin_t> txin_t::clone() const {
	return std::make_shared<txin_t>(*this);
}

void txin_t::read(vnx::TypeInput& _in, const vnx::TypeCode* _type_code, const uint16_t* _code) {
	vnx::read(_in, *this, _type_code, _code);
}

void txin_t::write(vnx::TypeOutput& _out, const vnx::TypeCode* _type_code, const uint16_t* _code) const {
	vnx::write(_out, *this, _type_code, _code);
}

void txin_t::accept(vnx::Visitor& _visitor) const {
	const vnx::TypeCode* _type_code = mmx::vnx_native_type_code_txin_t;
	_visitor.type_begin(*_type_code);
	_visitor.type_field(_type_code->fields[0], 0); vnx::accept(_visitor, address);
	_visitor.type_field(_type_code->fields[1], 1); vnx::accept(_visitor, contract);
	_visitor.type_field(_type_code->fields[2], 2); vnx::accept(_visitor, amount);
	_visitor.type_field(_type_code->fields[3], 3); vnx::accept(_visitor, memo);
	_visitor.type_field(_type_code->fields[4], 4); vnx::accept(_visitor, solution);
	_visitor.type_field(_type_code->fields[5], 5); vnx::accept(_visitor, flags);
	_visitor.type_end(*_type_code);
}

void txin_t::write(std::ostream& _out) const {
	_out << "{";
	_out << "\"address\": "; vnx::write(_out, address);
	_out << ", \"contract\": "; vnx::write(_out, contract);
	_out << ", \"amount\": "; vnx::write(_out, amount);
	_out << ", \"memo\": "; vnx::write(_out, memo);
	_out << ", \"solution\": "; vnx::write(_out, solution);
	_out << ", \"flags\": "; vnx::write(_out, flags);
	_out << "}";
}

void txin_t::read(std::istream& _in) {
	if(auto _json = vnx::read_json(_in)) {
		from_object(_json->to_object());
	}
}

vnx::Object txin_t::to_object() const {
	vnx::Object _object;
	_object["__type"] = "mmx.txin_t";
	_object["address"] = address;
	_object["contract"] = contract;
	_object["amount"] = amount;
	_object["memo"] = memo;
	_object["solution"] = solution;
	_object["flags"] = flags;
	return _object;
}

void txin_t::from_object(const vnx::Object& _object) {
	for(const auto& _entry : _object.field) {
		if(_entry.first == "address") {
			_entry.second.to(address);
		} else if(_entry.first == "amount") {
			_entry.second.to(amount);
		} else if(_entry.first == "contract") {
			_entry.second.to(contract);
		} else if(_entry.first == "flags") {
			_entry.second.to(flags);
		} else if(_entry.first == "memo") {
			_entry.second.to(memo);
		} else if(_entry.first == "solution") {
			_entry.second.to(solution);
		}
	}
}

vnx::Variant txin_t::get_field(const std::string& _name) const {
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
	if(_name == "solution") {
		return vnx::Variant(solution);
	}
	if(_name == "flags") {
		return vnx::Variant(flags);
	}
	return vnx::Variant();
}

void txin_t::set_field(const std::string& _name, const vnx::Variant& _value) {
	if(_name == "address") {
		_value.to(address);
	} else if(_name == "contract") {
		_value.to(contract);
	} else if(_name == "amount") {
		_value.to(amount);
	} else if(_name == "memo") {
		_value.to(memo);
	} else if(_name == "solution") {
		_value.to(solution);
	} else if(_name == "flags") {
		_value.to(flags);
	}
}

/// \private
std::ostream& operator<<(std::ostream& _out, const txin_t& _value) {
	_value.write(_out);
	return _out;
}

/// \private
std::istream& operator>>(std::istream& _in, txin_t& _value) {
	_value.read(_in);
	return _in;
}

const vnx::TypeCode* txin_t::static_get_type_code() {
	const vnx::TypeCode* type_code = vnx::get_type_code(VNX_TYPE_HASH);
	if(!type_code) {
		type_code = vnx::register_type_code(static_create_type_code());
	}
	return type_code;
}

std::shared_ptr<vnx::TypeCode> txin_t::static_create_type_code() {
	auto type_code = std::make_shared<vnx::TypeCode>();
	type_code->name = "mmx.txin_t";
	type_code->type_hash = vnx::Hash64(0xda6587114a2413full);
	type_code->code_hash = vnx::Hash64(0xf995f5e67a956c4eull);
	type_code->is_native = true;
	type_code->native_size = sizeof(::mmx::txin_t);
	type_code->parents.resize(1);
	type_code->parents[0] = ::mmx::txio_t::static_get_type_code();
	type_code->create_value = []() -> std::shared_ptr<vnx::Value> { return std::make_shared<vnx::Struct<txin_t>>(); };
	type_code->fields.resize(6);
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
	{
		auto& field = type_code->fields[4];
		field.data_size = 2;
		field.name = "solution";
		field.value = vnx::to_string(-1);
		field.code = {2};
	}
	{
		auto& field = type_code->fields[5];
		field.data_size = 1;
		field.name = "flags";
		field.code = {1};
	}
	type_code->build();
	return type_code;
}


} // namespace mmx


namespace vnx {

void read(TypeInput& in, ::mmx::txin_t& value, const TypeCode* type_code, const uint16_t* code) {
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
		if(const auto* const _field = type_code->field_map[4]) {
			vnx::read_value(_buf + _field->offset, value.solution, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[5]) {
			vnx::read_value(_buf + _field->offset, value.flags, _field->code.data());
		}
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

void write(TypeOutput& out, const ::mmx::txin_t& value, const TypeCode* type_code, const uint16_t* code) {
	if(code && code[0] == CODE_OBJECT) {
		vnx::write(out, value.to_object(), nullptr, code);
		return;
	}
	if(!type_code || (code && code[0] == CODE_ANY)) {
		type_code = mmx::vnx_native_type_code_txin_t;
		out.write_type_code(type_code);
		vnx::write_class_header<::mmx::txin_t>(out);
	}
	else if(code && code[0] == CODE_STRUCT) {
		type_code = type_code->depends[code[1]];
	}
	auto* const _buf = out.write(3);
	vnx::write_value(_buf + 0, value.solution);
	vnx::write_value(_buf + 2, value.flags);
	vnx::write(out, value.address, type_code, type_code->fields[0].code.data());
	vnx::write(out, value.contract, type_code, type_code->fields[1].code.data());
	vnx::write(out, value.amount, type_code, type_code->fields[2].code.data());
	vnx::write(out, value.memo, type_code, type_code->fields[3].code.data());
}

void read(std::istream& in, ::mmx::txin_t& value) {
	value.read(in);
}

void write(std::ostream& out, const ::mmx::txin_t& value) {
	value.write(out);
}

void accept(Visitor& visitor, const ::mmx::txin_t& value) {
	value.accept(visitor);
}

bool is_equivalent<::mmx::txin_t>::operator()(const uint16_t* code, const TypeCode* type_code) {
	if(code[0] != CODE_STRUCT || !type_code) {
		return false;
	}
	type_code = type_code->depends[code[1]];
	return type_code->type_hash == ::mmx::txin_t::VNX_TYPE_HASH && type_code->is_equivalent;
}

} // vnx
