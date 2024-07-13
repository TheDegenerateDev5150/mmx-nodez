
// AUTO GENERATED by vnxcppcodegen

#include <mmx/package.hxx>
#include <mmx/farmed_block_summary_t.hxx>
#include <mmx/addr_t.hpp>

#include <vnx/vnx.h>


namespace mmx {


const vnx::Hash64 farmed_block_summary_t::VNX_TYPE_HASH(0x9fe2bac01782721dull);
const vnx::Hash64 farmed_block_summary_t::VNX_CODE_HASH(0x8349f56d71a75ef6ull);

vnx::Hash64 farmed_block_summary_t::get_type_hash() const {
	return VNX_TYPE_HASH;
}

std::string farmed_block_summary_t::get_type_name() const {
	return "mmx.farmed_block_summary_t";
}

const vnx::TypeCode* farmed_block_summary_t::get_type_code() const {
	return mmx::vnx_native_type_code_farmed_block_summary_t;
}

std::shared_ptr<farmed_block_summary_t> farmed_block_summary_t::create() {
	return std::make_shared<farmed_block_summary_t>();
}

std::shared_ptr<farmed_block_summary_t> farmed_block_summary_t::clone() const {
	return std::make_shared<farmed_block_summary_t>(*this);
}

void farmed_block_summary_t::read(vnx::TypeInput& _in, const vnx::TypeCode* _type_code, const uint16_t* _code) {
	vnx::read(_in, *this, _type_code, _code);
}

void farmed_block_summary_t::write(vnx::TypeOutput& _out, const vnx::TypeCode* _type_code, const uint16_t* _code) const {
	vnx::write(_out, *this, _type_code, _code);
}

void farmed_block_summary_t::accept(vnx::Visitor& _visitor) const {
	const vnx::TypeCode* _type_code = mmx::vnx_native_type_code_farmed_block_summary_t;
	_visitor.type_begin(*_type_code);
	_visitor.type_field(_type_code->fields[0], 0); vnx::accept(_visitor, num_blocks);
	_visitor.type_field(_type_code->fields[1], 1); vnx::accept(_visitor, last_height);
	_visitor.type_field(_type_code->fields[2], 2); vnx::accept(_visitor, total_rewards);
	_visitor.type_field(_type_code->fields[3], 3); vnx::accept(_visitor, reward_map);
	_visitor.type_end(*_type_code);
}

void farmed_block_summary_t::write(std::ostream& _out) const {
	_out << "{";
	_out << "\"num_blocks\": "; vnx::write(_out, num_blocks);
	_out << ", \"last_height\": "; vnx::write(_out, last_height);
	_out << ", \"total_rewards\": "; vnx::write(_out, total_rewards);
	_out << ", \"reward_map\": "; vnx::write(_out, reward_map);
	_out << "}";
}

void farmed_block_summary_t::read(std::istream& _in) {
	if(auto _json = vnx::read_json(_in)) {
		from_object(_json->to_object());
	}
}

vnx::Object farmed_block_summary_t::to_object() const {
	vnx::Object _object;
	_object["__type"] = "mmx.farmed_block_summary_t";
	_object["num_blocks"] = num_blocks;
	_object["last_height"] = last_height;
	_object["total_rewards"] = total_rewards;
	_object["reward_map"] = reward_map;
	return _object;
}

void farmed_block_summary_t::from_object(const vnx::Object& _object) {
	for(const auto& _entry : _object.field) {
		if(_entry.first == "last_height") {
			_entry.second.to(last_height);
		} else if(_entry.first == "num_blocks") {
			_entry.second.to(num_blocks);
		} else if(_entry.first == "reward_map") {
			_entry.second.to(reward_map);
		} else if(_entry.first == "total_rewards") {
			_entry.second.to(total_rewards);
		}
	}
}

vnx::Variant farmed_block_summary_t::get_field(const std::string& _name) const {
	if(_name == "num_blocks") {
		return vnx::Variant(num_blocks);
	}
	if(_name == "last_height") {
		return vnx::Variant(last_height);
	}
	if(_name == "total_rewards") {
		return vnx::Variant(total_rewards);
	}
	if(_name == "reward_map") {
		return vnx::Variant(reward_map);
	}
	return vnx::Variant();
}

void farmed_block_summary_t::set_field(const std::string& _name, const vnx::Variant& _value) {
	if(_name == "num_blocks") {
		_value.to(num_blocks);
	} else if(_name == "last_height") {
		_value.to(last_height);
	} else if(_name == "total_rewards") {
		_value.to(total_rewards);
	} else if(_name == "reward_map") {
		_value.to(reward_map);
	}
}

/// \private
std::ostream& operator<<(std::ostream& _out, const farmed_block_summary_t& _value) {
	_value.write(_out);
	return _out;
}

/// \private
std::istream& operator>>(std::istream& _in, farmed_block_summary_t& _value) {
	_value.read(_in);
	return _in;
}

const vnx::TypeCode* farmed_block_summary_t::static_get_type_code() {
	const vnx::TypeCode* type_code = vnx::get_type_code(VNX_TYPE_HASH);
	if(!type_code) {
		type_code = vnx::register_type_code(static_create_type_code());
	}
	return type_code;
}

std::shared_ptr<vnx::TypeCode> farmed_block_summary_t::static_create_type_code() {
	auto type_code = std::make_shared<vnx::TypeCode>();
	type_code->name = "mmx.farmed_block_summary_t";
	type_code->type_hash = vnx::Hash64(0x9fe2bac01782721dull);
	type_code->code_hash = vnx::Hash64(0x8349f56d71a75ef6ull);
	type_code->is_native = true;
	type_code->native_size = sizeof(::mmx::farmed_block_summary_t);
	type_code->create_value = []() -> std::shared_ptr<vnx::Value> { return std::make_shared<vnx::Struct<farmed_block_summary_t>>(); };
	type_code->fields.resize(4);
	{
		auto& field = type_code->fields[0];
		field.data_size = 4;
		field.name = "num_blocks";
		field.code = {3};
	}
	{
		auto& field = type_code->fields[1];
		field.data_size = 4;
		field.name = "last_height";
		field.code = {3};
	}
	{
		auto& field = type_code->fields[2];
		field.data_size = 8;
		field.name = "total_rewards";
		field.code = {4};
	}
	{
		auto& field = type_code->fields[3];
		field.is_extended = true;
		field.name = "reward_map";
		field.code = {13, 5, 11, 32, 1, 4};
	}
	type_code->build();
	return type_code;
}


} // namespace mmx


namespace vnx {

void read(TypeInput& in, ::mmx::farmed_block_summary_t& value, const TypeCode* type_code, const uint16_t* code) {
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
			vnx::read_value(_buf + _field->offset, value.num_blocks, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[1]) {
			vnx::read_value(_buf + _field->offset, value.last_height, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[2]) {
			vnx::read_value(_buf + _field->offset, value.total_rewards, _field->code.data());
		}
	}
	for(const auto* _field : type_code->ext_fields) {
		switch(_field->native_index) {
			case 3: vnx::read(in, value.reward_map, type_code, _field->code.data()); break;
			default: vnx::skip(in, type_code, _field->code.data());
		}
	}
}

void write(TypeOutput& out, const ::mmx::farmed_block_summary_t& value, const TypeCode* type_code, const uint16_t* code) {
	if(code && code[0] == CODE_OBJECT) {
		vnx::write(out, value.to_object(), nullptr, code);
		return;
	}
	if(!type_code || (code && code[0] == CODE_ANY)) {
		type_code = mmx::vnx_native_type_code_farmed_block_summary_t;
		out.write_type_code(type_code);
		vnx::write_class_header<::mmx::farmed_block_summary_t>(out);
	}
	else if(code && code[0] == CODE_STRUCT) {
		type_code = type_code->depends[code[1]];
	}
	auto* const _buf = out.write(16);
	vnx::write_value(_buf + 0, value.num_blocks);
	vnx::write_value(_buf + 4, value.last_height);
	vnx::write_value(_buf + 8, value.total_rewards);
	vnx::write(out, value.reward_map, type_code, type_code->fields[3].code.data());
}

void read(std::istream& in, ::mmx::farmed_block_summary_t& value) {
	value.read(in);
}

void write(std::ostream& out, const ::mmx::farmed_block_summary_t& value) {
	value.write(out);
}

void accept(Visitor& visitor, const ::mmx::farmed_block_summary_t& value) {
	value.accept(visitor);
}

bool is_equivalent<::mmx::farmed_block_summary_t>::operator()(const uint16_t* code, const TypeCode* type_code) {
	if(code[0] != CODE_STRUCT || !type_code) {
		return false;
	}
	type_code = type_code->depends[code[1]];
	return type_code->type_hash == ::mmx::farmed_block_summary_t::VNX_TYPE_HASH && type_code->is_equivalent;
}

} // vnx
