/*
 * Compiler.cpp
 *
 *  Created on: Dec 10, 2022
 *      Author: mad
 */

#include <mmx/vm/Compiler.h>
#include <mmx/vm/Engine.h>
#include <mmx/vm/instr_t.h>
#include <mmx/vm/varptr_t.hpp>
#include <mmx/vm_interface.h>
#include <mmx/helpers.h>

#include <lexy/dsl.hpp>
#include <lexy/callback.hpp>
#include <lexy/action/parse_as_tree.hpp>
#include <lexy/action/trace.hpp>
#include <lexy/input/string_input.hpp>
#include <lexy_ext/parse_tree_algorithm.hpp>
#include <lexy_ext/report_error.hpp>
#include <lexy_ext/shell.hpp>

#include <uint256_t.h>

#include <memory>
#include <iostream>

#include "std/embedded.h"


namespace mmx {
namespace vm {

namespace lang {

namespace dsl = lexy::dsl;

struct source;
struct statement;
struct expression;

static constexpr auto ws = dsl::whitespace(dsl::ascii::space);
static constexpr auto kw_id = dsl::identifier(dsl::ascii::alpha_underscore, dsl::ascii::alpha_digit_underscore);

static constexpr auto kw_if = LEXY_KEYWORD("if", kw_id);
static constexpr auto kw_do = LEXY_KEYWORD("do", kw_id);
static constexpr auto kw_in = LEXY_KEYWORD("in", kw_id);
static constexpr auto kw_of = LEXY_KEYWORD("of", kw_id);
static constexpr auto kw_this = LEXY_KEYWORD("this", kw_id);
static constexpr auto kw_for = LEXY_KEYWORD("for", kw_id);
static constexpr auto kw_else = LEXY_KEYWORD("else", kw_id);
static constexpr auto kw_while = LEXY_KEYWORD("while", kw_id);
static constexpr auto kw_var = LEXY_KEYWORD("var", kw_id);
static constexpr auto kw_let = LEXY_KEYWORD("let", kw_id);
static constexpr auto kw_null = LEXY_KEYWORD("null", kw_id);
static constexpr auto kw_true = LEXY_KEYWORD("true", kw_id);
static constexpr auto kw_false = LEXY_KEYWORD("false", kw_id);
static constexpr auto kw_const = LEXY_KEYWORD("const", kw_id);
static constexpr auto kw_public = LEXY_KEYWORD("public", kw_id);
static constexpr auto kw_payable = LEXY_KEYWORD("payable", kw_id);
static constexpr auto kw_static = LEXY_KEYWORD("static", kw_id);
static constexpr auto kw_export = LEXY_KEYWORD("export", kw_id);
static constexpr auto kw_return = LEXY_KEYWORD("return", kw_id);
static constexpr auto kw_function = LEXY_KEYWORD("function", kw_id);
static constexpr auto kw_namespace = LEXY_KEYWORD("package", kw_id);
static constexpr auto kw_continue = LEXY_KEYWORD("continue", kw_id);
static constexpr auto kw_break = LEXY_KEYWORD("break", kw_id);
static constexpr auto kw_interface = LEXY_KEYWORD("interface", kw_id);
static constexpr auto kw_import = LEXY_KEYWORD("import", kw_id);
static constexpr auto kw_from = LEXY_KEYWORD("from", kw_id);

struct comment {
	static constexpr auto name = "mmx.lang.comment";
	static constexpr auto rule = LEXY_LIT("//") >> dsl::loop(
			(dsl::ascii::newline >> dsl::break_) |
			(dsl::eof >> dsl::break_) |
			 dsl::ascii::character);
};

struct reserved {
	static constexpr auto name = "mmx.lang.reserved";
	static constexpr auto rule = dsl::literal_set(
			kw_if, kw_do, kw_for, kw_else, kw_while, kw_var, kw_let,
			kw_null, kw_true, kw_false, kw_const, kw_public, kw_return,
			kw_function, kw_namespace, kw_this, kw_export, kw_static, kw_continue,
			kw_break, kw_interface, kw_import);
};

struct expected_identifier {
	static constexpr auto name = "expected identifier";
};

struct identifier : lexy::token_production {
	static constexpr auto name = "mmx.lang.identifier";
	static constexpr auto rule = kw_id;
};

struct restricted_identifier : lexy::transparent_production {
	struct invalid_reserved {
		static constexpr auto name = "invalid identifier: reserved keyword";
	};
	static constexpr auto name = "mmx.lang.restricted_identifier";
	static constexpr auto rule = dsl::peek(dsl::p<reserved>) >> dsl::error<invalid_reserved> | dsl::p<identifier>;
};

struct primitive : lexy::token_production {
	static constexpr auto name = "mmx.lang.primitive";
	static constexpr auto rule = dsl::literal_set(kw_null, kw_true, kw_false);
};

struct integer : lexy::transparent_production {
	struct invalid_integer {
		static constexpr auto name = "invalid integer";
	};
	struct hex : lexy::token_production {
		static constexpr auto name = "mmx.lang.integer.hex";
		static constexpr auto rule =
				dsl::digits<dsl::hex> >> dsl::if_(dsl::peek(dsl::ascii::alpha_underscore) >> dsl::error<invalid_integer>);
	};
	struct binary : lexy::token_production {
		static constexpr auto name = "mmx.lang.integer.binary";
		static constexpr auto rule =
				dsl::digits<dsl::binary> >> dsl::if_(dsl::peek(dsl::ascii::alpha_digit_underscore) >> dsl::error<invalid_integer>);
	};
	struct decimal : lexy::token_production {
		static constexpr auto name = "mmx.lang.integer.decimal";
		static constexpr auto rule =
				dsl::digits<dsl::decimal> >> dsl::if_(dsl::peek(dsl::ascii::alpha_underscore) >> dsl::error<invalid_integer>);
	};
	static constexpr auto name = "mmx.lang.integer";
	static constexpr auto rule =
			(LEXY_LIT("0b") >> dsl::p<binary>) | (LEXY_LIT("0x") >> dsl::p<hex>) | dsl::p<decimal>;
};

struct string : lexy::token_production {
	static constexpr auto name = "mmx.lang.string";
	static constexpr auto rule = dsl::quoted(-dsl::ascii::control, dsl::backslash_escape);
};

struct address : lexy::token_production {
	static constexpr auto name = "mmx.lang.address";
	static constexpr auto rule =
			dsl::peek(LEXY_LIT("mmx1")) >> dsl::identifier(dsl::ascii::alpha_digit);
};

struct constant {
	static constexpr auto name = "mmx.lang.constant";
	static constexpr auto rule =
			dsl::p<primitive> | dsl::p<address> | dsl::p<string> | dsl::p<integer>;
};

struct import_list {
	static constexpr auto name = "mmx.lang.import_list";
	static constexpr auto rule = dsl::curly_bracketed.list(dsl::recurse<restricted_identifier>, dsl::sep(dsl::comma));
};

struct import {
	static constexpr auto name = "mmx.lang.import";
	static constexpr auto rule =
			kw_import >> dsl::p<import_list> + kw_from + dsl::p<string>;
};

struct scope {
	static constexpr auto name = "mmx.lang.scope";
	static constexpr auto rule = dsl::curly_bracketed(dsl::recurse<source>);
};

struct namespace_ex {
	static constexpr auto name = "mmx.lang.namespace";
	static constexpr auto rule = kw_namespace >> dsl::p<restricted_identifier> + dsl::p<scope>;
};

struct expected_constant {
	static constexpr auto name = "expected a constant";
};

struct function {
	struct arguments {
		struct item {
			static constexpr auto name = "mmx.lang.function.arguments.item";
			static constexpr auto rule = dsl::p<restricted_identifier> +
					dsl::opt(dsl::equal_sign >> (dsl::p<constant> | dsl::error<expected_constant>));
		};
		static constexpr auto name = "mmx.lang.function.arguments";
		static constexpr auto rule = dsl::parenthesized.opt_list(dsl::p<item>, dsl::sep(dsl::comma));
	};
	struct qualifier {
		static constexpr auto name = "mmx.lang.function.qualifier";
		static constexpr auto rule = dsl::literal_set(kw_const, kw_public, kw_payable, kw_static);
	};
	static constexpr auto name = "mmx.lang.function";
	static constexpr auto rule = kw_function >>
			dsl::p<restricted_identifier> + dsl::p<arguments> + dsl::while_(dsl::p<qualifier>) + dsl::p<scope>;
};

struct operator_ex : lexy::token_production {
	static constexpr auto name = "mmx.lang.operator";
	static constexpr auto rule = dsl::literal_set(
			dsl::lit_c<'.'>, dsl::lit_c<'+'>, dsl::lit_c<'-'>, dsl::lit_c<'*'>, dsl::lit_c<'/'>, dsl::lit_c<'!'>, dsl::lit_c<'='>,
			dsl::lit_c<'>'>, dsl::lit_c<'<'>, dsl::lit_c<'&'>, dsl::lit_c<'|'>, dsl::lit_c<'^'>, dsl::lit_c<'~'>, dsl::lit_c<'%'>,
			LEXY_LIT(">="), LEXY_LIT("<="), LEXY_LIT("=="), LEXY_LIT("!="), LEXY_LIT("^^"), LEXY_LIT("&&"), LEXY_LIT("||"),
			LEXY_LIT("++"), LEXY_LIT("--"), LEXY_LIT(">>"), LEXY_LIT("<<"), LEXY_LIT("+="), LEXY_LIT("-="),
			LEXY_LIT("*="), LEXY_LIT("/="), LEXY_LIT("^="), LEXY_LIT("&="), LEXY_LIT("|="),
			LEXY_LIT("^^="), LEXY_LIT("&&="), LEXY_LIT("||="), LEXY_LIT(">>="), LEXY_LIT("<<="), kw_return);
};

struct qualifier : lexy::token_production {
	static constexpr auto name = "mmx.lang.qualifier";
	static constexpr auto rule = dsl::literal_set(kw_let, kw_var, kw_const);
};

struct variable {
	static constexpr auto name = "mmx.lang.variable";
	static constexpr auto rule = dsl::p<qualifier> >>
			dsl::p<restricted_identifier> + dsl::opt(dsl::equal_sign >> dsl::recurse<expression>);
};

struct interface {
	static constexpr auto name = "mmx.lang.interface";
	static constexpr auto rule = kw_interface >> dsl::p<restricted_identifier>;
};

struct array {
	static constexpr auto name = "mmx.lang.array";
	static constexpr auto rule = dsl::square_bracketed.opt_list(dsl::recurse<expression>, dsl::trailing_sep(dsl::comma));
};

struct object {
	struct expected_key {
		static constexpr auto name = "expected key";
	};
	struct entry {
		static constexpr auto name = "mmx.lang.object.entry";
		static constexpr auto rule =
				(dsl::p<string> | dsl::p<identifier> | dsl::error<expected_key>) + dsl::lit_c<':'> + dsl::recurse<expression>;
	};
	static constexpr auto name = "mmx.lang.object";
	static constexpr auto rule = dsl::curly_bracketed.opt_list(dsl::p<entry>, dsl::trailing_sep(dsl::comma));
};

struct sub_expr {
	static constexpr auto name = "mmx.lang.sub_expr";
	static constexpr auto rule = dsl::parenthesized.opt_list(dsl::recurse<expression>, dsl::sep(dsl::comma));
};

struct expression {
	static constexpr auto name = "mmx.lang.expression";
	static constexpr auto rule = dsl::loop(
			dsl::peek_not(dsl::comma | dsl::semicolon | dsl::lit_c<')'> | dsl::lit_c<']'> | dsl::lit_c<'}'> | dsl::eof) >> (
					dsl::p<sub_expr> | dsl::p<array> | dsl::p<object> | dsl::p<operator_ex> | dsl::p<constant> |
					dsl::else_ >> dsl::p<identifier>
			) | dsl::break_);
};

struct statement {
	static constexpr auto name = "mmx.lang.statement";
	static constexpr auto rule =
			(dsl::p<variable> | dsl::p<interface> | dsl::p<import> | kw_break | kw_continue | dsl::else_ >> dsl::p<expression>) + dsl::semicolon;
};

struct else_ex;

struct if_ex {
	static constexpr auto name = "mmx.lang.if";
	static constexpr auto rule = kw_if >>
			dsl::parenthesized(dsl::p<expression>) + (dsl::p<scope> | dsl::else_ >> dsl::p<statement>)
			+ dsl::if_(dsl::peek(kw_else) >> dsl::recurse<else_ex>);
};

struct else_ex {
	static constexpr auto name = "mmx.lang.else";
	static constexpr auto rule = kw_else +
			((dsl::peek(kw_if) >> dsl::recurse<if_ex>) | dsl::p<scope> | dsl::else_ >> dsl::p<statement>)
			+ dsl::if_(dsl::peek(kw_else) >> dsl::recurse<else_ex>);
};

struct for_loop {
	static constexpr auto name = "mmx.lang.for";
	static constexpr auto rule = kw_for >>
			dsl::parenthesized.opt_list(
					(dsl::p<variable> >> dsl::opt(kw_of >> dsl::p<expression>)) |
					dsl::else_ >> dsl::p<expression>, dsl::trailing_sep(dsl::comma | dsl::semicolon))
			+ (dsl::p<scope> | dsl::else_ >> dsl::p<statement>);
};

struct while_loop {
	static constexpr auto name = "mmx.lang.while";
	static constexpr auto rule = kw_while >>
			dsl::parenthesized(dsl::p<expression>) + (dsl::p<scope> | dsl::else_ >> dsl::p<statement>);
};

struct source {
	static constexpr auto name = "mmx.lang.source";
	static constexpr auto whitespace = dsl::inline_<comment> | dsl::ascii::space;
	static constexpr auto rule = dsl::loop(
			dsl::peek_not(dsl::lit_c<'}'> | dsl::eof) >> (
					dsl::p<namespace_ex> | dsl::p<scope> | dsl::p<function> |
					dsl::p<if_ex> | dsl::p<for_loop> | dsl::p<while_loop> |
					dsl::else_ >> dsl::p<statement>
			) | dsl::break_);
};

} // lang


template<typename Node>
void dump_parse_tree(const Node& node, std::ostream& out, int depth = 0, int offset = 0)
{
	out << (depth < 10 ? " " : "") << depth << ":" << (offset < 10 ? " " : "") << offset << " ";

	for(int i = 0; i < depth; ++i) {
		out << "  ";
	}
	const std::string name(node.kind().name());
	out << name;

	if(node.kind().is_token()) {
		const auto token = node.lexeme();
		out << ": " << vnx::to_string(std::string(token.begin(), token.end()));
	}
	out << std::endl;

	int i = 0;
	for(const auto& child : node.children()) {
		const std::string name(child.kind().name());
		if(name != "whitespace") {
			dump_parse_tree(child, out, depth + 1, i++);
		}
	}
}


class Compiler {
public:
	static const std::string version;

	const compile_flags_t flags;

	Compiler(const compile_flags_t& flags = compile_flags_t());

	std::shared_ptr<const contract::Binary> compile(const std::string& source);

protected:
	typedef lexy::parse_tree<lexy::input_reader<lexy::string_input<lexy::utf8_encoding>>> parse_tree_t;
	typedef typename parse_tree_t::node node_t;

	struct variable_t {
		bool is_const = false;
		bool is_static = false;
		uint32_t address = 0;
		std::string name;
		varptr_t value;
	};

	struct function_t {
		bool is_init = false;
		bool is_const = false;
		bool is_public = false;
		bool is_payable = false;
		uint32_t address = 0;
		std::string name;
		std::vector<variable_t> args;
		vnx::optional<node_t> root;
	};

	struct frame_t {
		uint32_t section = MEM_STACK;
		uint32_t addr_offset = 0;
		std::vector<variable_t> var_list;
		std::map<std::string, uint32_t> var_map;

		uint32_t new_addr() {
			return section + addr_offset++;
		}
		void add_variable(const variable_t& var) {
			if(var.name.size()) {
				if(!var_map.emplace(var.name, var_list.size()).second) {
					throw std::logic_error("duplicate variable name: " + var.name);
				}
			}
			var_list.push_back(var);
		}
	};

	struct vref_t {
		bool is_const = false;
		bool is_interface = false;
		uint32_t address = -1;
		vnx::optional<uint32_t> key;
		vnx::optional<function_t> func;
		vnx::optional<std::string> name;
		vnx::optional<std::string> method;

		vref_t() = default;
		vref_t(uint32_t address) : address(address) {}
		vref_t(uint32_t address, std::string name) : address(address), name(name) {}
		vref_t(uint32_t address, uint32_t key) : address(address), key(key) {}
		vref_t(const std::string& name) : name(name) {}
		vref_t(const function_t& func) : func(func), name(func.name) {}

		void check_value() const {
			if(func) {
				throw std::logic_error("expected value not function");
			}
			if(is_interface) {
				throw std::logic_error("expected value not interface");
			}
			if(address == uint32_t(-1) && name) {
				throw std::logic_error("no such variable: " + (*name));
			}
		}
		bool is_mutable() const {
			return !is_const || key;
		}
	};

	void parse(parse_tree_t& tree);

	vref_t recurse(const node_t& node);

	vref_t recurse_expr(const node_t*& p_node, size_t& expr_len, const vref_t* lhs = nullptr, const int lhs_rank = -1);

	vref_t copy(const vref_t& dst, const vref_t& src, const bool validate = true);

	uint32_t get(const vref_t& src, const uint32_t* dst = nullptr);

	void push_scope();

	void pop_scope();

	const variable_t* find_variable(const std::string& name) const;

	const function_t* find_function(const std::string& name) const;

	variable_t get_variable(const std::string& name);

	uint32_t get_const_address(const varptr_t& value);

	uint32_t get_const_address(const uint256_t& value);

	uint32_t get_const_address(const addr_t& value);

	uint32_t get_const_address(const std::string& value);

	int get_node_rank(const node_t& node) const;

	std::string get_namespace(const bool concat = false) const;

	std::ostream& debug(bool ident = false) const;

	void print_debug_info(const node_t& node) const;

	void handle_new_code();

	uint32_t get_line_number(const node_t& node) const;

	static std::vector<node_t> get_children(const node_t& node);

	static std::string to_source(const node_t& node);

	static std::string get_literal(const node_t& node);

	static varptr_t parse_constant(const node_t& node);

private:
	int depth = 0;
	int curr_pass = 0;

	uint8_t math_flags = 0;

	size_t code_offset = 0;
	vnx::optional<node_t> curr_node;
	vnx::optional<function_t> curr_function;

	frame_t global;
	std::vector<instr_t> code;
	std::vector<frame_t> frame;
	std::vector<variable_t> const_vars;
	std::vector<std::string> name_space;

	std::map<varptr_t, uint32_t> const_table;
	std::set<std::string> interface_set;
	std::map<std::string, function_t> function_map;
	std::map<uint32_t, uint32_t> line_info;
	std::map<uint32_t, std::string> linker_map;
	std::map<std::string, int> rank_map;
	std::map<std::string, int> simple_code_map;
	std::map<std::string, uint32_t> this_obj_map;

	std::string source;
	std::shared_ptr<contract::Binary> binary;

	mutable std::stringstream debug_out;

};

const std::string Compiler::version = "1.0.0";

Compiler::Compiler(const compile_flags_t& flags)
	:	flags(flags)
{
	if(flags.catch_overflow) {
		math_flags |= OPFLAG_CATCH_OVERFLOW;
	}

	int rank = 0;
	rank_map["position"] = -1;
	rank_map[lang::constant::name] = rank++;
	rank_map[lang::identifier::name] = rank++;
	rank_map["."] = rank++;
	rank_map[lang::array::name] = rank++;
	rank_map[lang::sub_expr::name] = rank++;
	rank_map[lang::object::name] = rank++;
	rank_map["++"] = rank;
	rank_map["--"] = rank++;
	rank_map["!"] = rank;
	rank_map["~"] = rank++;
	rank_map["*"] = rank;
	rank_map["/"] = rank;
	rank_map["%"] = rank++;
	rank_map["+"] = rank;
	rank_map["-"] = rank++;
	rank_map[">>"] = rank;
	rank_map["<<"] = rank++;
	rank_map["<"] = rank;
	rank_map[">"] = rank;
	rank_map["<="] = rank;
	rank_map[">="] = rank++;
	rank_map["!="] = rank;
	rank_map["=="] = rank++;
	rank_map["&"] = rank;
	rank_map["&&"] = rank++;
	rank_map["^"] = rank;
	rank_map["^^"] = rank++;
	rank_map["|"] = rank;
	rank_map["||"] = rank++;
	rank_map["="] = rank;
	rank_map["+="] = rank;
	rank_map["-="] = rank;
	rank_map["*="] = rank;
	rank_map["/="] = rank;
	rank_map["^="] = rank;
	rank_map["&="] = rank;
	rank_map["|="] = rank;
	rank_map["^^="] = rank;
	rank_map["&&="] = rank;
	rank_map["||="] = rank;
	rank_map[">>="] = rank;
	rank_map["<<="] = rank++;
	rank_map["break"] = rank;
	rank_map["continue"] = rank;
	rank_map["return"] = rank++;
	rank_map[lang::expression::name] = rank++;

	simple_code_map["+"] = OP_ADD;
	simple_code_map["-"] = OP_SUB;
	simple_code_map["*"] = OP_MUL;
	simple_code_map["/"] = OP_DIV;
	simple_code_map["%"] = OP_MOD;
	simple_code_map["&"] = OP_AND;
	simple_code_map["&&"] = OP_AND;
	simple_code_map["|"] = OP_OR;
	simple_code_map["||"] = OP_OR;
	simple_code_map["^"] = OP_XOR;
	simple_code_map["^^"] = OP_XOR;
	simple_code_map[">"] = OP_CMP_GT;
	simple_code_map["<"] = OP_CMP_LT;
	simple_code_map[">="] = OP_CMP_GTE;
	simple_code_map["<="] = OP_CMP_LTE;
	simple_code_map["!="] = OP_CMP_NEQ;
	simple_code_map["=="] = OP_CMP_EQ;

	this_obj_map["height"] = MEM_EXTERN + EXTERN_HEIGHT;
	this_obj_map["txid"] = MEM_EXTERN + EXTERN_TXID;
	this_obj_map["user"] = MEM_EXTERN + EXTERN_USER;
	this_obj_map["balance"] = MEM_EXTERN + EXTERN_BALANCE;
	this_obj_map["address"] = MEM_EXTERN + EXTERN_ADDRESS;
	this_obj_map["deposit"] = MEM_EXTERN + EXTERN_DEPOSIT;

	function_map["__nop"].name = "__nop";
	function_map["__copy"].name = "__copy";
	function_map["size"].name = "size";
	function_map["push"].name = "push";
	function_map["pop"].name = "pop";
	function_map["set"].name = "set";
	function_map["get"].name = "get";
	function_map["min"].name = "min";
	function_map["max"].name = "max";
	function_map["clone"].name = "clone";
	function_map["deref"].name = "deref";
	function_map["erase"].name = "erase";
	function_map["delete"].name = "delete";
	function_map["typeof"].name = "typeof";
	function_map["concat"].name = "concat";
	function_map["memcpy"].name = "memcpy";
	function_map["send"].name = "send";
	function_map["mint"].name = "mint";
	function_map["fail"].name = "fail";
	function_map["log"].name = "log";
	function_map["event"].name = "event";
	function_map["read"].name = "read";
	function_map["bech32"].name = "bech32";
	function_map["binary"].name = "binary";
	function_map["binary_le"].name = "binary_le";
	function_map["binary_hex"].name = "binary_hex";
	function_map["bool"].name = "bool";
	function_map["uint"].name = "uint";
	function_map["uint_le"].name = "uint_le";
	function_map["uint_hex"].name = "uint_hex";
	function_map["sha256"].name = "sha256";
	function_map["ecdsa_verify"].name = "ecdsa_verify";
	function_map["string"].name = "string";
	function_map["string_hex"].name = "string_hex";
	function_map["string_bech32"].name = "string_bech32";
	function_map["rcall"].name = "rcall";
	function_map["balance"].name = "balance";
	function_map["is_uint"].name = "is_uint";
	function_map["is_string"].name = "is_string";
	function_map["is_binary"].name = "is_binary";
	function_map["is_array"].name = "is_array";
	function_map["is_map"].name = "is_map";
	function_map["assert"].name = "assert";

	global.section = MEM_STATIC;

	// address zero = null value
	if(get_const_address(std::make_unique<var_t>())) {
		throw std::logic_error("zero address not null");
	}
}

std::shared_ptr<const contract::Binary> Compiler::compile(const std::string& source_)
{
	if(curr_pass) {
		throw std::logic_error("invalid state");
	}
	source = source_;
	{
		// resolve imports
		parse_tree_t tree;
		parse(tree);

		for(const auto& node : get_children(tree.root())) {
			const std::string name(node.kind().name());
			if(name == lang::statement::name) {
				const auto list = get_children(node);
				if(!list.empty()) {
					const auto node = list[0];
					const std::string name(node.kind().name());
					if(name == lang::import::name) try {
						const auto list = get_children(node);
						if(list.size() != 4) {
							throw std::logic_error("invalid import");
						}
						std::set<std::string> units;
						const auto import_list = list[1];
						for(const auto& node : get_children(import_list)) {
							const std::string name(node.kind().name());
							if(name == lang::identifier::name) {
								units.insert(get_literal(node));
							}
						}
						const auto module = get_literal(list[3]);
						if(module == "std") {
							for(const auto& unit : units) {
								const auto key = unit + ".js";
								if(!std_file_map.count(key)) {
									throw std::logic_error("unknown unit '" + unit + "'");
								}
								source += "\n// Imported from std/" + key + "\n";
								source += std_file_map[key];
							}
						} else {
							throw std::logic_error("unknown module '" + module + "'");
						}
					}
					catch(const std::exception& ex) {
						dump_parse_tree(tree.root(), debug());
						throw std::logic_error("error at line " + std::to_string(get_line_number(node)) + ": " + ex.what());
					}
				}
			}
		}
	}

	binary = std::make_shared<contract::Binary>();
	binary->source = source;
	binary->compiler = std::string("mmx") + "-" + version;
	binary->build_flags = flags;

	parse_tree_t tree;
	parse(tree);

	debug() << std::endl;
	dump_parse_tree(tree.root(), debug());
	debug() << std::endl;

	try {
		// static init stack frame
		frame.emplace_back();

		debug() << "First pass ..." << std::endl;

		recurse(tree.root());

		curr_pass++;
		frame.clear();

		debug() << std::endl << "Second pass ..." << std::endl;

		for(const auto& entry : function_map) {
			const auto& func = entry.second;
			if(const auto& node = func.root) {
				recurse(*node);
			}
		}
		for(const auto& entry : linker_map) {
			if(auto func = find_function(entry.second)) {
				code[entry.first].a = func->address;
			} else {
				throw std::runtime_error("undefined reference to function '" + entry.second + "'");
			}
		}
	}
	catch(const std::exception& ex) {
		if(curr_node) {
			throw std::logic_error(std::string("error at line ") + std::to_string(get_line_number(*curr_node)) + ": " + ex.what());
		} else {
			throw std::logic_error(std::string("error: ") +  + ex.what());
		}
	}

	for(const auto& var : const_vars) {
		if(!var.value) {
			throw std::logic_error("missing constant value");
		}
		const auto data = serialize(*var.value, false, false);
		binary->constant.insert(binary->constant.end(), data.first.get(), data.first.get() + data.second);
	}
	for(const auto& var : global.var_list) {
		if(var.is_static) {
			binary->fields[var.name] = var.address;
		}
	}
	for(const auto& entry : function_map) {
		const auto& func = entry.second;
		if(func.root) {
			contract::method_t method;
			method.name = func.name;
			method.entry_point = func.address;
			method.is_init = func.is_init;
			method.is_const = func.is_const;
			method.is_public = func.is_public;
			method.is_payable = func.is_payable;
			for(const auto& arg : func.args) {
				method.args.push_back(arg.name);
			}
			binary->methods[method.name] = method;
		}
	}
	binary->binary = vm::serialize(code);
	{
		uint32_t prev = 0;
		for(const auto& entry : line_info) {
			if(entry.second != prev) {
				binary->line_info.insert(entry);
				prev = entry.second;
			}
		}
	}
	debug() << std::endl;
	dump_code(debug(), binary);
	return binary;
}

void Compiler::parse(parse_tree_t& tree)
{
	const auto result = lexy::parse_as_tree<lang::source>(
			tree, lexy::string_input<lexy::utf8_encoding>(source), lexy_ext::report_error);

	if(!result.is_success()) {
		throw std::runtime_error("parse() failed");
	}
}

std::vector<Compiler::node_t> Compiler::get_children(const node_t& node)
{
	std::vector<Compiler::node_t> list;
	for(const auto& child : node.children()) {
		const std::string name(child.kind().name());
		if(name != "whitespace") {
			list.push_back(child);
		}
	}
	return list;
}

uint32_t Compiler::get_line_number(const node_t& node) const
{
	const auto loc = lexy::get_input_location(
			lexy::string_input<lexy::utf8_encoding>(source), node.position());
	return loc.line_nr();
}

std::string Compiler::to_source(const node_t& node)
{
    std::string source;
    if(node.kind().is_token()) {
        const auto token = node.lexeme();
        source.append(token.begin(), token.end());
    } else {
        for(const auto& child : node.children()) {
            source += to_source(child);
        }
    }
    std::string out;
    for(auto c : source) {
        switch(c) {
			case '\r': break;
			case '\n': out += "\\n"; break;
            case '\t': out += "\\t"; break;
            default: out += c; break;
        }
    }
    return out;
}

std::string Compiler::get_literal(const node_t& node)
{
	if(node.kind().is_token()) {
		const auto token = node.lexeme();
		return std::string(token.begin(), token.end());
	} else {
		const auto list = get_children(node);
		const std::string name(node.kind().name());
		if(name == lang::string::name && list.size() == 3) {
			return get_literal(list[1]);
		} else {
			if(list.size() != 1) {
				throw std::logic_error("not a literal: " + std::string(node.kind().name()));
			}
			return get_literal(list[0]);
		}
	}
}

varptr_t Compiler::parse_constant(const node_t& node)
{
	const auto list = get_children(node);
	const std::string name(node.kind().name());

	if(name == lang::expression::name) {
		if(list.size() == 1) {
			return parse_constant(list[0]);
		}
	}
	else if(name == lang::constant::name) {
		if(list.size() > 2) {
			throw std::logic_error("invalid constant");
		}
		return parse_constant(list.back());
	}
	else if(name == lang::primitive::name) {
		if(list.size() != 1) {
			throw std::logic_error("invalid primitive");
		}
		const auto value = get_literal(list[0]);
		if(value == "null") {
			return std::make_unique<var_t>();
		} else if(value == "true") {
			return std::make_unique<var_t>(TYPE_TRUE);
		} else if(value == "false") {
			return std::make_unique<var_t>(TYPE_FALSE);
		}
	}
	else if(name == lang::integer::hex::name) {
		return std::make_unique<uint_t>(uint256_t(get_literal(list[0]), 16));
	}
	else if(name == lang::integer::binary::name) {
		return std::make_unique<uint_t>(uint256_t(get_literal(list[0]), 2));
	}
	else if(name == lang::integer::decimal::name) {
		return std::make_unique<uint_t>(uint256_t(get_literal(list[0]), 10));
	}
	else if(name == lang::string::name) {
		if(list.size() == 3) {
			return binary_t::alloc(get_literal(list[1]));
		} else if(list.size() == 2) {
			return binary_t::alloc("");
		} else {
			throw std::logic_error("invalid string");
		}
	}
	else if(name == lang::address::name) {
		if(list.size() != 1) {
			throw std::logic_error("invalid address");
		}
		return to_binary(addr_t(get_literal(list[0])));
	}
	return nullptr;
}

int Compiler::get_node_rank(const node_t& node) const
{
	const std::string name(node.kind().name());

	std::string key;
	if(name == lang::operator_ex::name) {
		key = get_literal(node);
	} else {
		key = name;
	}
	auto iter = rank_map.find(key);
	if(iter == rank_map.end()) {
		throw std::logic_error("missing rank for " + name);
	}
	return iter->second;
}

std::string Compiler::get_namespace(const bool concat) const
{
	std::string res;
	for(const auto& name : name_space) {
		if(!res.empty()) {
			res += ".";
		}
		res += name;
	}
	if(concat && !res.empty()) {
		res += ".";
	}
	return res;
}

std::ostream& Compiler::debug(bool ident) const
{
	auto& out = flags.verbose ? std::cerr : debug_out;
	for(int i = 0; ident && i < depth; ++i) {
		out << "  ";
	}
	return out;
}

void Compiler::print_debug_info(const node_t& node) const
{
	debug(true) << node.kind().name();

	if(node.kind().is_token()) {
		const auto token = node.lexeme();
		debug() << ": " << vnx::to_string(std::string(token.begin(), token.end()));
	}
	debug() << std::endl;
}

void Compiler::handle_new_code()
{
	vnx::optional<uint32_t> line;
	if(curr_node) {
		line = get_line_number(*curr_node);
	}
	for(auto i = code_offset; i < code.size(); ++i) {
		if(line) {
			line_info[i] = *line;
		}
		debug(true) << to_string(code[i]) << std::endl;
	}
	code_offset = code.size();
}

Compiler::vref_t Compiler::recurse(const node_t& node)
{
	handle_new_code();
	print_debug_info(node);

	vref_t out;
	curr_node = node;
	depth++;

	const std::string name(node.kind().name());
	const std::string p_name(node.parent().kind().name());
	const auto list = get_children(node);

	if(name == lang::import::name) {
		// ignore here
	}
	else if(name == lang::namespace_ex::name)
	{
		if(list.size() < 2) {
			throw std::logic_error("invalid namespace declaration");
		}
		const auto name = get_literal(list[1]);
		debug(true) << "name = \"" << name << "\"" << std::endl;

//		name_space.push_back(name);
		for(const auto& node : list) {
			recurse(node);
		}
//		name_space.pop_back();
	}
	else if(name == lang::scope::name)
	{
		if(list.size() != 3) {
			throw std::logic_error("invalid scope");
		}
		push_scope();
		recurse(list[1]);
		pop_scope();
	}
	else if(name == lang::source::name)
	{
		for(const auto& node : list) {
			recurse(node);
		}
		if(curr_pass == 0 && frame.size() == 1) {
			// return from static init
			code.emplace_back(OP_RET);
		}
	}
	else if(name == lang::function::name)
	{
		if(list.size() < 3) {
			throw std::logic_error("invalid function declaration");
		}
		if(curr_pass == 0) {
			function_t func;
			func.root = node;
			func.name = get_namespace(true) + get_literal(list[1]);

			if(func.name == "init") {
				func.is_init = true;
			}
			if(func.name == "deposit") {
				func.is_payable = true;
			}
			debug(true) << "name = \"" << func.name << "\"" << std::endl;

			if(function_map.count(func.name)) {
				throw std::logic_error("duplicate function name");
			}
			for(const auto& arg : get_children(list[2]))
			{
				const std::string name(arg.kind().name());
				if(name == lang::function::arguments::item::name) {
					const auto list = get_children(arg);
					if(list.size() < 1) {
						throw std::logic_error("invalid function argument");
					}
					const std::string name(list[0].kind().name());
					if(name != lang::identifier::name) {
						throw std::logic_error("expected argument identifier");
					}
					variable_t var;
					var.name = get_literal(list[0]);
					var.address = MEM_STACK + 1 + func.args.size();

					debug(true) << "[" << func.args.size() << "] " << var.name;
					if(list.size() == 3) {
						var.value = parse_constant(list[2]);
						debug() << " = " << to_string(var.value);
					} else if(list.size() != 1) {
						throw std::logic_error("invalid function argument");
					}
					debug() << std::endl;

					func.args.push_back(var);
				}
			}
			for(size_t i = 3; i < list.size(); ++i)
			{
				const auto node = list[i];
				const std::string name(node.kind().name());
				if(name == lang::function::qualifier::name) {
					const auto list = get_children(node);
					if(list.size() != 1) {
						throw std::logic_error("invalid function qualifier");
					}
					const auto value = get_literal(list[0]);
					if(value == "const") {
						func.is_const = true;
						debug(true) << "is_const = true" << std::endl;
					}
					else if(value == "public") {
						func.is_public = true;
						debug(true) << "is_public = true" << std::endl;
					}
					else if(value == "payable") {
						func.is_payable = true;
						debug(true) << "is_payable = true" << std::endl;
					}
					else if(value == "static") {
						func.is_init = true;
					}
					else {
						throw std::logic_error("invalid function qualifier");
					}
				}
			}
			if(func.is_init) {
				debug(true) << "is_init = true" << std::endl;
				if(func.is_const) {
					throw std::logic_error("constructor cannot be const");
				}
				if(func.is_public) {
					throw std::logic_error("constructor cannot be public");
				}
				if(func.is_payable) {
					throw std::logic_error("constructor cannot be payable");
				}
			}
			function_map[func.name] = func;
		} else {
			// second pass
			const auto func_name = get_namespace(true) + get_literal(list[1]);
			debug(true) << "name = \"" << func_name << "\"" << std::endl;

			if(curr_function) {
				throw std::logic_error("cannot define function inside a function");
			}
			auto& func = function_map[func_name];
			func.address = code.size();
			debug(true) << "address = 0x" << std::hex << func.address << std::dec << std::endl;

			frame_t scope;
			scope.addr_offset = 1 + func.args.size();
			for(const auto& arg : func.args) {
				scope.add_variable(arg);
			}
			curr_function = func;

			if(func.is_init) {
				code.emplace_back(OP_CALL, 0, 0, scope.new_addr() - MEM_STACK);
			}
			frame.push_back(scope);
			code.emplace_back(OP_COPY, 0, MEM_STACK, 0);
			recurse(list.back());
			frame.pop_back();

			if(code.empty() || code.back().code != OP_RET) {
				code.emplace_back(OP_RET);
			}
			curr_function = nullptr;
		}
	}
	else if(name == lang::variable::name)
	{
		if(list.size() < 2) {
			throw std::logic_error("invalid variable declaration");
		}
		const auto qualifier = get_literal(list[0]);

		variable_t var;
		var.is_const = (qualifier == "const");
		var.name = get_literal(list[1]);

		bool is_constant = false;
		bool is_expression = false;

		if(list.size() == 4) {
			const auto value = parse_constant(list[3]);
			if(var.is_const && value) {
				is_constant = true;
				var.value = value;
			} else {
				is_expression = true;
			}
		} else if(list.size() != 2) {
			throw std::logic_error("invalid variable declaration");
		}
		var.is_static = !is_constant && frame.size() == 1;

		auto& scope = frame.size() == 1 ? global : frame.back();
		if(is_constant) {
			var.address = get_const_address(var.value);
		} else {
			var.address = scope.new_addr();
		}

		debug(true) << qualifier << " " << var.name;
		if(is_constant) {
			debug() << " = " << to_string(var.value);
		}
		if(is_expression) {
			debug() << " = <expression>";
		}
		debug() << " (0x" << std::hex << var.address << std::dec << ")" << std::endl;

		if(is_expression) {
			copy(var.address, recurse(list.back()));
		} else if(!is_constant) {
			copy(var.address, 0);
		}
		scope.add_variable(var);

		out.address = var.address;
	}
	else if(name == lang::interface::name)
	{
		if(list.size() != 2) {
			throw std::logic_error("invalid interface declaration");
		}
		const auto qualifier = get_literal(list[0]);
		const auto name = get_literal(list[1]);
		debug(true) << qualifier << " " << name << std::endl;
		if(!interface_set.emplace(name).second) {
			throw std::logic_error("duplicate interface declaration");
		}
	}
	else if(name == lang::if_ex::name)
	{
		if(list.size() < 5) {
			throw std::logic_error("invalid if()");
		}
		const auto cond = get(recurse(list[2]));
		const auto jump = code.size();
		code.emplace_back(OP_JUMPN, 0, -1, cond);
		recurse(list[4]);

		if(list.size() == 6) {
			const auto skip = code.size();
			code.emplace_back(OP_JUMP, 0, -1);
			code[jump].a = code.size();
			recurse(list[5]);
			code[skip].a = code.size();
		} else {
			code[jump].a = code.size();
		}
	}
	else if(name == lang::else_ex::name)
	{
		if(list.size() < 2) {
			throw std::logic_error("invalid else");
		}
		recurse(list[1]);
	}
	else if(name == lang::while_loop::name)
	{
		if(list.size() < 5) {
			throw std::logic_error("invalid while()");
		}
		const auto begin = code.size();
		const auto cond = get(recurse(list[2]));
		const auto jump = code.size();
		code.emplace_back(OP_JUMPN, 0, -1, cond);
		recurse(list.back());
		code.emplace_back(OP_JUMP, 0, begin);
		code[jump].a = code.size();
	}
	else if(name == lang::for_loop::name)
	{
		if(list.size() < 5) {
			throw std::logic_error("invalid for()");
		}
		bool is_range = false;
		std::vector<std::list<node_t>> nodes;
		nodes.emplace_back();
		for(size_t i = 2; i + 1 < list.size(); ++i) {
			const auto& node = list[i];
			const std::string name(node.kind().name());
			if(name == "literal") {
				const auto lit = get_literal(node);
				if(lit == ";") {
					nodes.emplace_back();
				} else if(lit == "of") {
					if(nodes.back().size() != 1) {
						throw std::logic_error("invalid range for()");
					}
					is_range = true;
				}
			} else {
				nodes.back().push_back(node);
			}
		}
		push_scope();

		if(is_range) {
			if(nodes.size() != 1) {
				throw std::logic_error("invalid range for()");
			}
			const auto& range_ex = nodes.front();
			if(range_ex.size() != 2) {
				throw std::logic_error("invalid range for()");
			}
			auto iter = range_ex.begin();
			const auto var_addr = get(recurse(*iter)); iter++;
			const auto range_addr = get(recurse(*iter));

			auto& stack = frame.back();
			const auto counter = stack.new_addr();
			copy(counter, get_const_address(uint256_t(0)));
			const auto size = stack.new_addr();
			code.emplace_back(OP_SIZE, OPFLAG_REF_B, size, range_addr);
			const auto begin = code.size();
			const auto cond = stack.new_addr();
			code.emplace_back(OP_CMP_LT, 0, cond, counter, size);
			const auto jump = code.size();
			code.emplace_back(OP_JUMPN, 0, -1, cond);
			code.emplace_back(OP_GET, OPFLAG_REF_B, var_addr, range_addr, counter);
			recurse(list.back());
			code.emplace_back(OP_ADD, OPFLAG_CATCH_OVERFLOW, counter, counter, get_const_address(1));
			code.emplace_back(OP_JUMP, 0, begin);
			code[jump].a = code.size();
		}
		else if(nodes.size() == 3) {
			if(nodes[1].size() != 1) {
				throw std::logic_error("invalid for() condition");
			}
			for(const auto& node : nodes[0]) {
				recurse(node);
			}
			const auto begin = code.size();
			const auto cond = get(recurse(nodes[1].front()));
			const auto jump = code.size();
			code.emplace_back(OP_JUMPN, 0, -1, cond);
			recurse(list.back());

			for(const auto& node : nodes[2]) {
				recurse(node);
			}
			code.emplace_back(OP_JUMP, 0, begin);
			code[jump].a = code.size();
		}
		else {
			throw std::logic_error("invalid for()");
		}
		pop_scope();
	}
	else if(name == lang::statement::name)
	{
		if(list.size() != 2) {
			throw std::logic_error("invalid statement");
		}
		recurse(list[0]);
	}
	else if(name == lang::expression::name)
	{
		auto p_node = list.data();
		auto expr_len = list.size();
		out = recurse_expr(p_node, expr_len);

		if(expr_len != 0) {
			throw std::logic_error("invalid expression");
		}
		out.check_value();
	}
	else if(name == "position")
	{
		// ignore dummy position nodes by lexy
	}
	else {
		throw std::logic_error("invalid statement: " + name);
	}

	handle_new_code();
	depth--;

	return out;
}

Compiler::vref_t Compiler::recurse_expr(const node_t*& p_node, size_t& expr_len, const vref_t* lhs, const int lhs_rank)
{
	if(expr_len == 0) {
		return lhs ? *lhs : vref_t();
	}
	const auto node = p_node[0];
	const auto rank = get_node_rank(node);

	if(lhs_rank >= 0 && rank >= lhs_rank) {
		if(!lhs) {
			throw std::logic_error("invalid expression");
		}
		return *lhs;
	}
	p_node++;
	expr_len--;

	vref_t out;
	auto& stack = frame.back();
	const std::string name(node.kind().name());
	const auto list = get_children(node);

	debug(true) << name << " (rank = " << rank << ", expr_len = " << expr_len << ", list = " << list.size() << ")" << std::endl;
	depth++;

	if(name == lang::identifier::name)
	{
		if(lhs) {
			throw std::logic_error("invalid expression");
		}
		const auto name = get_literal(node);

		if(auto var = find_variable(name)) {
			out.address = var->address;
			out.is_const = var->is_const;
		}
		else if(auto func = find_function(name)) {
			out.func = *func;
			out.address = func->address;
		}
		else if(interface_set.count(name)) {
			out.is_interface = true;
		}
		out.name = name;
	}
	else if(name == lang::array::name)
	{
		if(lhs) {
			if(list.size() != 3) {
				throw std::logic_error("invalid bracket operator");
			}
			const auto key = recurse(list[1]);

			if(key.key) {
				out.key = copy(stack.new_addr(), key).address;
			} else {
				out.key = key.address;
			}
			if(lhs->key) {
				out.address = copy(stack.new_addr(), *lhs).address;
			} else {
				out.address = lhs->address;
			}
			lhs->check_value();
		} else {
			out.address = stack.new_addr();
			code.emplace_back(OP_CLONE, 0, out.address, get_const_address(std::make_unique<array_t>()));

			for(const auto& node : list) {
				const std::string name(node.kind().name());
				if(name == lang::expression::name) {
					const auto value = recurse(node);
					code.emplace_back(OP_PUSH_BACK, OPFLAG_REF_A, out.address, get(value));
				}
			}
		}
	}
	else if(name == lang::operator_ex::name)
	{
		const auto op = get_literal(node);

		bool is_assign = false;
		auto iter = simple_code_map.find(op);
		if(iter == simple_code_map.end() && !op.empty() && op.back() == '=') {
			is_assign = true;
			iter = simple_code_map.find(op.substr(0, op.size() - 1));
		}
		if(iter != simple_code_map.end()) {
			if(!lhs) {
				throw std::logic_error("missing left operand");
			}
			if(expr_len < 1) {
				throw std::logic_error("missing right operand");
			}
			int op_flags = 0;
			auto op_code = opcode_e(iter->second);
			switch(op_code) {
				case OP_ADD:
				case OP_SUB:
				case OP_MUL:
				case OP_DIV:
				case OP_MOD:
					op_flags |= math_flags;
					break;
				case OP_XOR:
				case OP_AND:
				case OP_OR:
					if(op == "^" || op == "&" || op == "|" || op == "^=" || op == "&=" || op == "|=") {
						op_flags |= OPFLAG_BITWISE;
					}
					break;
				default:
					break;
			}
			auto rhs = get(recurse_expr(p_node, expr_len, nullptr, rank));

			switch(op_code) {
				case OP_DIV:
				case OP_MOD:
					if(rhs < const_vars.size() && flags.opt_level > 0) {
						// optimize division by power of two
						if(const auto& value = const_vars[rhs].value) {
							if(value->type == TYPE_UINT) {
								const auto& uint = ((const uint_t*)value.get())->value;
								if(uint != 0 && (uint & (uint - 1)) == 0) {
									int count = 0;
									auto tmp = uint;
									for(; count <= 256 && !(tmp & 1); ++count, tmp >>= 1);
									if(count < 256) {
										debug(false) << "Optimizing DIV / MOD by power of two: " << uint << " => " << count << std::endl;
										switch(op_code) {
											case OP_DIV:
												op_code = OP_SHR;
												op_flags = 0;
												rhs = count;
												break;
											case OP_MOD:
												op_code = OP_AND;
												op_flags = OPFLAG_BITWISE;
												rhs = get_const_address((uint256_1 << count) - 1);
												break;
											default:
												break;
										}
									}
								}
							}
						}
					}
					break;
				default:
					break;
			}
			if(is_assign) {
				if(lhs->key) {
					const auto tmp_addr = stack.new_addr();
					code.emplace_back(op_code, op_flags, tmp_addr, get(*lhs), rhs);
					copy(*lhs, tmp_addr);
				} else {
					lhs->check_value();
					code.emplace_back(op_code, op_flags, lhs->address, lhs->address, rhs);
				}
				out = *lhs;
			} else {
				out.address = stack.new_addr();
				code.emplace_back(op_code, op_flags, out.address, get(*lhs), rhs);
			}
		}
		else if(op == "=") {
			if(!lhs) {
				throw std::logic_error("missing left operand");
			}
			if(!lhs->is_mutable()) {
				if(lhs->name) {
					throw std::logic_error("cannot assign to const variable: " + *lhs->name);
				} else {
					throw std::logic_error("assignment to const variable");
				}
			}
			if(expr_len < 1) {
				throw std::logic_error("missing right operand");
			}
			const auto rhs = recurse_expr(p_node, expr_len, nullptr, rank);
			out = copy(*lhs, rhs);
		}
		else if(op == ".") {
			if(!lhs) {
				throw std::logic_error("missing left operand");
			}
			if(expr_len < 1) {
				throw std::logic_error("missing right operand");
			}
			const auto rhs = recurse_expr(p_node, expr_len, nullptr, rank);

			if(!rhs.name) {
				throw std::logic_error("expected identifier");
			}
			const auto key = *rhs.name;

			if(lhs->is_interface && !lhs->method) {
				out = *lhs;
				out.method = key;
			}
			else if(lhs->name && *lhs->name == "this" && !lhs->key) {
				auto iter = this_obj_map.find(key);
				if(iter == this_obj_map.end()) {
					throw std::logic_error("no such variable: this." + key);
				}
				out.address = iter->second;
				out.is_const = true;
			}
			else if(lhs->address == MEM_EXTERN + EXTERN_DEPOSIT && !lhs->key) {
				out = *lhs;
				if(key == "currency") {
					out.key = get_const_address(uint256_t(0));
				} else if(key == "amount") {
					out.key = get_const_address(uint256_t(1));
				} else {
					throw std::logic_error("no such variable: this.deposit." + key);
				}
			}
			else {
				out.address = get(*lhs);
				out.key = get_const_address(key);
				out.is_const = lhs->is_const;
			}
		}
		else if(op == "!" || op == "~") {
			if(lhs) {
				throw std::logic_error("unexpected left operand");
			}
			if(expr_len < 1) {
				throw std::logic_error("missing right operand");
			}
			const auto rhs = recurse_expr(p_node, expr_len, nullptr, rank);
			out.address = stack.new_addr();
			code.emplace_back(OP_NOT, op == "~" ? OPFLAG_BITWISE : 0, out.address, get(rhs));
		}
		else if(op == "++" || op == "--") {
			if(lhs) {
				if(lhs->is_const) {
					throw std::logic_error("operand is const");
				}
				out.address = copy(stack.new_addr(), *lhs).address;
				const auto tmp_addr = lhs->key ? stack.new_addr() : lhs->address;
				code.emplace_back(op == "++" ? OP_ADD : OP_SUB, math_flags, tmp_addr, out.address, get_const_address(1));
				copy(*lhs, tmp_addr);
			} else {
				if(expr_len < 1) {
					throw std::logic_error("missing right operand");
				}
				out = recurse_expr(p_node, expr_len, nullptr, rank);
				if(out.is_const) {
					throw std::logic_error("operand is const");
				}
				const auto tmp_addr = out.key ? copy(stack.new_addr(), out).address : out.address;
				code.emplace_back(op == "++" ? OP_ADD : OP_SUB, math_flags, tmp_addr, tmp_addr, get_const_address(1));
				copy(out, tmp_addr);
			}
		}
		else if(op == ">>" || op == "<<") {
			if(!lhs) {
				throw std::logic_error("missing left operand");
			}
			out.address = stack.new_addr();
			const auto rhs = recurse_expr(p_node, expr_len, nullptr, rank);
			code.emplace_back(op == ">>" ? OP_SHR : OP_SHL, OPFLAG_REF_C, out.address, get(*lhs), get(rhs));
		}
		else if(op == "return") {
			if(lhs) {
				throw std::logic_error("unexpected left operand");
			}
			if(expr_len > 0) {
				copy(MEM_STACK, recurse_expr(p_node, expr_len, nullptr, rank));
			}
			code.emplace_back(OP_RET);
		}
		else {
			throw std::logic_error("invalid operator: " + op);
		}
	}
	else if(name == lang::sub_expr::name)
	{
		std::vector<node_t> args;
		for(const auto& node : list) {
			const std::string name(node.kind().name());
			if(name == lang::expression::name) {
				args.push_back(node);
			}
		}
		if(lhs && lhs->func) {
			const auto& name = lhs->func->name;

			if(name == "__nop") {
				if(args.size()) {
					throw std::logic_error("expected 0 arguments for __nop()");
				}
				code.emplace_back(OP_NOP);
			}
			else if(name == "size") {
				if(args.size() != 1) {
					throw std::logic_error("expected 1 argument for size()");
				}
				out.address = stack.new_addr();
				code.emplace_back(OP_SIZE, OPFLAG_REF_B, out.address, get(recurse(args[0])));
			}
			else if(name == "push") {
				if(args.size() < 2) {
					throw std::logic_error("expected 2 or more arguments for push(array, value)");
				}
				const auto array = get(recurse(args[0]));
				for(size_t i = 1; i < args.size(); ++i) {
					code.emplace_back(OP_PUSH_BACK, OPFLAG_REF_A, array, get(recurse(args[i])));
				}
				out.address = 0;
			}
			else if(name == "pop") {
				if(args.size() != 1) {
					throw std::logic_error("expected 1 argument for pop()");
				}
				out.address = stack.new_addr();
				code.emplace_back(OP_POP_BACK, OPFLAG_REF_B, out.address, get(recurse(args[0])));
			}
			else if(name == "set") {
				if(args.size() != 3) {
					throw std::logic_error("expected 3 arguments for set(..., key, value)");
				}
				out.address = get(recurse(args[2]));
				code.emplace_back(OP_SET, OPFLAG_REF_A, get(recurse(args[0])), get(recurse(args[1])), out.address);
			}
			else if(name == "get") {
				if(args.size() != 2) {
					throw std::logic_error("expected 2 arguments for get()");
				}
				out.address = stack.new_addr();
				code.emplace_back(OP_GET, OPFLAG_REF_B, out.address, get(recurse(args[0])), get(recurse(args[1])));
			}
			else if(name == "min" || name == "max") {
				if(args.size() < 2) {
					throw std::logic_error("expected 2 or more arguments for " + name + "()");
				}
				out.address = stack.new_addr();
				auto lhs = get(recurse(args[0]));
				for(size_t i = 1; i < args.size(); ++i) {
					code.emplace_back(name == "min" ? OP_MIN : OP_MAX, 0, out.address, lhs, get(recurse(args[i])));
					lhs = out.address;
				}
			}
			else if(name == "__copy") {
				if(args.size() != 2) {
					throw std::logic_error("expected 2 arguments for __copy(dst, src)");
				}
				copy(recurse(args[0]), recurse(args[1]), false);
				out.address = 0;
			}
			else if(name == "clone") {
				if(args.size() != 1) {
					throw std::logic_error("expected 1 argument for clone()");
				}
				out.address = stack.new_addr();
				code.emplace_back(OP_CLONE, OPFLAG_REF_B, out.address, get(recurse(args[0])));
			}
			else if(name == "deref") {
				if(args.size() != 1) {
					throw std::logic_error("expected 1 argument for deref()");
				}
				out.address = stack.new_addr();
				code.emplace_back(OP_COPY, OPFLAG_REF_B, out.address, get(recurse(args[0])));
			}
			else if(name == "delete") {
				if(args.size() != 1) {
					throw std::logic_error("expected 1 argument for delete()");
				}
				code.emplace_back(OP_CLR, 0, get(recurse(args[0])));
				out.address = 0;
			}
			else if(name == "erase") {
				if(args.size() != 2) {
					throw std::logic_error("expected 2 arguments for erase(object, key)");
				}
				out.address = 0;
				code.emplace_back(OP_ERASE, OPFLAG_REF_A, get(recurse(args[0])), get(recurse(args[1])));
			}
			else if(name == "typeof") {
				if(args.size() != 1) {
					throw std::logic_error("expected 1 argument for typeof()");
				}
				out.address = stack.new_addr();
				code.emplace_back(OP_TYPE, OPFLAG_REF_B, out.address, get(recurse(args[0])));
			}
			else if(name == "is_uint") {
				if(args.size() != 1) {
					throw std::logic_error("expected 1 argument for is_uint()");
				}
				out.address = stack.new_addr();
				code.emplace_back(OP_TYPE, OPFLAG_REF_B, out.address, get(recurse(args[0])));
				code.emplace_back(OP_CMP_EQ, 0, out.address, out.address, get_const_address(int(TYPE_UINT)));
			}
			else if(name == "is_string") {
				if(args.size() != 1) {
					throw std::logic_error("expected 1 argument for is_string()");
				}
				out.address = stack.new_addr();
				code.emplace_back(OP_TYPE, OPFLAG_REF_B, out.address, get(recurse(args[0])));
				code.emplace_back(OP_CMP_EQ, 0, out.address, out.address, get_const_address(int(TYPE_STRING)));
			}
			else if(name == "is_binary") {
				if(args.size() != 1) {
					throw std::logic_error("expected 1 argument for is_binary()");
				}
				out.address = stack.new_addr();
				code.emplace_back(OP_TYPE, OPFLAG_REF_B, out.address, get(recurse(args[0])));
				code.emplace_back(OP_CMP_EQ, 0, out.address, out.address, get_const_address(int(TYPE_BINARY)));
			}
			else if(name == "is_array") {
				if(args.size() != 1) {
					throw std::logic_error("expected 1 argument for is_array()");
				}
				out.address = stack.new_addr();
				code.emplace_back(OP_TYPE, OPFLAG_REF_B, out.address, get(recurse(args[0])));
				code.emplace_back(OP_CMP_EQ, 0, out.address, out.address, get_const_address(int(TYPE_ARRAY)));
			}
			else if(name == "is_map") {
				if(args.size() != 1) {
					throw std::logic_error("expected 1 argument for is_map()");
				}
				out.address = stack.new_addr();
				code.emplace_back(OP_TYPE, OPFLAG_REF_B, out.address, get(recurse(args[0])));
				code.emplace_back(OP_CMP_EQ, 0, out.address, out.address, get_const_address(int(TYPE_MAP)));
			}
			else if(name == "concat") {
				if(args.size() < 2) {
					throw std::logic_error("expected 2 or more arguments for concat()");
				}
				auto lhs = get(recurse(args[0]));
				for(size_t i = 1; i < args.size(); ++i) {
					out.address = stack.new_addr();
					code.emplace_back(OP_CONCAT, OPFLAG_REF_B | OPFLAG_REF_C, out.address, lhs, get(recurse(args[i])));
					lhs = out.address;
				}
			}
			else if(name == "send") {
				if(args.size() < 2 || args.size() > 4) {
					throw std::logic_error("expected 2 to 4 arguments for send(address, amount, [currency], [memo])");
				}
				code.emplace_back(OP_SEND, 0, get(recurse(args[0])), get(recurse(args[1])),
						args.size() > 2 ? get(recurse(args[2])) : get_const_address(addr_t()),
						args.size() > 3 ? get(recurse(args[3])) : 0);
				out.address = 0;
			}
			else if(name == "mint") {
				if(args.size() < 2 || args.size() > 3) {
					throw std::logic_error("expected 2 to 3 arguments for mint(address, amount, [memo])");
				}
				code.emplace_back(OP_MINT, 0, get(recurse(args[0])), get(recurse(args[1])),
						args.size() > 2 ? get(recurse(args[2])) : 0);
				out.address = 0;
			}
			else if(name == "fail") {
				if(args.size() != 1 && args.size() != 2) {
					throw std::logic_error("expected 1 or 2 arguments for fail(message, [code])");
				}
				code.emplace_back(OP_FAIL, args.size() > 1 ? OPFLAG_REF_B : 0,
						get(recurse(args[0])),
						args.size() > 1 ? get(recurse(args[1])) : 0);
				out.address = 0;
			}
			else if(name == "log") {
				if(args.size() != 2) {
					throw std::logic_error("expected 2 arguments for log(level, message)");
				}
				code.emplace_back(OP_LOG, OPFLAG_REF_A, get(recurse(args[0])), get(recurse(args[1])));
				out.address = 0;
			}
			else if(name == "event") {
				if(args.size() != 2) {
					throw std::logic_error("expected 2 arguments for event(name, data)");
				}
				code.emplace_back(OP_EVENT, 0, get(recurse(args[0])), get(recurse(args[1])));
				out.address = 0;
			}
			else if(name == "read") {
				out.address = stack.new_addr();
				if(args.size() == 2) {
					code.emplace_back(OP_CREAD, 0, out.address, get(recurse(args[1])), get(recurse(args[0])));
				} else if(args.size() == 1) {
					code.emplace_back(OP_CREAD, 0, out.address, MEM_EXTERN + EXTERN_ADDRESS, get(recurse(args[0])));
				} else {
					throw std::logic_error("expected 1 or 2 arguments for read(field, [address])");
				}
			}
			else if(name == "bech32") {
				if(args.size() == 0) {
					out.address = stack.new_addr();
					code.emplace_back(OP_COPY, 0, out.address, get_const_address(addr_t()));
				} else if(args.size() == 1) {
					out.address = stack.new_addr();
					code.emplace_back(OP_CONV, 0, out.address, get(recurse(args[0])), CONVTYPE_ADDRESS, CONVTYPE_DEFAULT);
				} else {
					throw std::logic_error("expected 0 or 1 argument for bech32()");
				}
			}
			else if(name == "binary") {
				if(args.size() != 1) {
					throw std::logic_error("expected 1 argument for binary()");
				}
				out.address = stack.new_addr();
				code.emplace_back(OP_CONV, 0, out.address, get(recurse(args[0])), CONVTYPE_BINARY, CONVTYPE_DEFAULT);
			}
			else if(name == "binary_le") {
				if(args.size() != 1) {
					throw std::logic_error("expected 1 argument for binary_le()");
				}
				out.address = stack.new_addr();
				code.emplace_back(OP_CONV, 0, out.address, get(recurse(args[0])), (CONVTYPE_BINARY | (CONVTYPE_LITTLE_ENDIAN << 8)), CONVTYPE_DEFAULT);
			}
			else if(name == "binary_hex") {
				if(args.size() != 1) {
					throw std::logic_error("expected 1 argument for binary_hex()");
				}
				out.address = stack.new_addr();
				code.emplace_back(OP_CONV, 0, out.address, get(recurse(args[0])), CONVTYPE_BINARY, CONVTYPE_BASE_16);
			}
			else if(name == "bool") {
				if(args.size() != 1) {
					throw std::logic_error("expected 1 argument for bool()");
				}
				out.address = stack.new_addr();
				code.emplace_back(OP_CONV, 0, out.address, get(recurse(args[0])), CONVTYPE_BOOL, CONVTYPE_DEFAULT);
			}
			else if(name == "uint") {
				if(args.size() != 1) {
					throw std::logic_error("expected 1 argument for uint()");
				}
				out.address = stack.new_addr();
				code.emplace_back(OP_CONV, 0, out.address, get(recurse(args[0])), CONVTYPE_UINT, CONVTYPE_DEFAULT);
			}
			else if(name == "uint_le") {
				if(args.size() != 1) {
					throw std::logic_error("expected 1 argument for uint_le()");
				}
				out.address = stack.new_addr();
				code.emplace_back(OP_CONV, 0, out.address, get(recurse(args[0])), CONVTYPE_UINT, CONVTYPE_LITTLE_ENDIAN);
			}
			else if(name == "uint_hex") {
				if(args.size() != 1) {
					throw std::logic_error("expected 1 argument for uint_hex()");
				}
				out.address = stack.new_addr();
				code.emplace_back(OP_CONV, 0, out.address, get(recurse(args[0])), CONVTYPE_UINT, CONVTYPE_BASE_16);
			}
			else if(name == "sha256") {
				if(args.size() != 1) {
					throw std::logic_error("expected 1 argument for sha256()");
				}
				out.address = stack.new_addr();
				code.emplace_back(OP_SHA256, 0, out.address, get(recurse(args[0])));
			}
			else if(name == "ecdsa_verify") {
				if(args.size() != 3) {
					throw std::logic_error("expected 3 arguments for ecdsa_verify(msg, pubkey, signature)");
				}
				out.address = stack.new_addr();
				code.emplace_back(OP_VERIFY, 0, out.address, get(recurse(args[0])), get(recurse(args[1])), get(recurse(args[2])));
			}
			else if(name == "string") {
				if(args.size() != 1) {
					throw std::logic_error("expected 1 argument for string()");
				}
				out.address = stack.new_addr();
				code.emplace_back(OP_CONV, 0, out.address, get(recurse(args[0])), CONVTYPE_STRING, CONVTYPE_DEFAULT);
			}
			else if(name == "string_hex") {
				if(args.size() != 1) {
					throw std::logic_error("expected 1 argument for string_hex()");
				}
				out.address = stack.new_addr();
				code.emplace_back(OP_CONV, 0, out.address, get(recurse(args[0])), CONVTYPE_STRING | (CONVTYPE_BASE_16 << 8), CONVTYPE_DEFAULT);
			}
			else if(name == "string_bech32") {
				if(args.size() != 1) {
					throw std::logic_error("expected 1 argument for string_bech32()");
				}
				out.address = stack.new_addr();
				code.emplace_back(OP_CONV, 0, out.address, get(recurse(args[0])), CONVTYPE_STRING | (CONVTYPE_ADDRESS << 8), CONVTYPE_DEFAULT);
			}
			else if(name == "memcpy") {
				if(args.size() < 2 || args.size() > 3) {
					throw std::logic_error("expected 2 to 3 arguments for memcpy(src, count, [offset])");
				}
				out.address = stack.new_addr();
				code.emplace_back(OP_MEMCPY, OPFLAG_REF_C | OPFLAG_REF_D, out.address,
						get(recurse(args[0])), get(recurse(args[1])),
						(args.size() > 2 ? get(recurse(args[2])) : get_const_address(uint256_0)));
			}
			else if(name == "rcall") {
				if(args.size() < 2) {
					throw std::logic_error("expected at least two arguments for rcall(contract, method, ...)");
				}
				const auto contract = get(recurse(args[0]));
				const auto method = get(recurse(args[1]));

				std::vector<vref_t> fargs;
				for(size_t i = 2; i < args.size(); ++i) {
					fargs.push_back(recurse(args[i]));	// collect arguments first
				}
				const auto offset = stack.new_addr();
				for(size_t i = 0; i < fargs.size(); ++i) {
					copy(offset + 1 + i, fargs[i]);
				}
				code.emplace_back(OP_RCALL, 0, contract, method, offset - MEM_STACK, args.size() - 2);
				out.address = offset;
			}
			else if(name == "balance") {
				if(args.size() > 1) {
					throw std::logic_error("expected at most one argument for balance([currency])");
				}
				const auto currency = args.size() > 0 ? get(recurse(args[0])) : get_const_address(addr_t());
				out.address = stack.new_addr();
				code.emplace_back(OP_BALANCE, 0, out.address, currency);
			}
			else if(name == "assert") {
				if(args.size() < 1 || args.size() > 3) {
					throw std::logic_error("expected 1-3 arguments for assert(condition, [message], [code])");
				}
				code.emplace_back(OP_JUMPI, 0, code.size() + 2, get(recurse(args[0])));
				if(args.size() == 1) {
					code.emplace_back(OP_FAIL, 0, get_const_address("assert(" + to_source(args[0]) + ")"));
				} else {
					code.emplace_back(OP_FAIL, args.size() > 2 ? OPFLAG_REF_B : 0,
							get(recurse(args[1])),
							args.size() > 2 ? get(recurse(args[2])) : 0);
				}
				out.address = 0;
			}
			else {
				if(curr_function && curr_function->is_const && lhs->func->root && !lhs->func->is_const) {
					throw std::logic_error("cannot call non-const function inside const function: " + name);
				}
				if(args.size() > lhs->func->args.size()) {
					throw std::logic_error("too many function arguments: "
							+ std::to_string(args.size()) + " > " + std::to_string(lhs->func->args.size()));
				}
				std::vector<vref_t> fargs;
				for(size_t i = 0; i < args.size(); ++i) {
					fargs.push_back(recurse(args[i]));	// collect arguments first
				}
				const auto offset = stack.new_addr();
				for(size_t i = 0; i < fargs.size(); ++i) {
					copy(offset + 1 + i, fargs[i]);
				}
				for(size_t i = args.size(); i < lhs->func->args.size(); ++i) {
					const auto& var = lhs->func->args[i];
					code.emplace_back(OP_COPY, 0, offset + 1 + i, var.value ? get_const_address(var.value) : 0);
				}
				linker_map[code.size()] = name;
				code.emplace_back(OP_CALL, 0, -1, offset - MEM_STACK);
				out.address = offset;
			}
		}
		else if(lhs && lhs->is_interface) {
			if(!lhs->name) {
				throw std::logic_error("missing interface name");
			}
			if(!lhs->method) {
				throw std::logic_error("missing method name");
			}
			const auto contract = get_const_address(*lhs->name);
			const auto method = get_const_address(*lhs->method);

			std::vector<vref_t> fargs;
			for(size_t i = 0; i < args.size(); ++i) {
				fargs.push_back(recurse(args[i]));	// collect arguments first
			}
			const auto offset = stack.new_addr();
			for(size_t i = 0; i < fargs.size(); ++i) {
				copy(offset + 1 + i, fargs[i]);
			}
			code.emplace_back(OP_RCALL, 0, contract, method, offset - MEM_STACK, args.size());
			out.address = offset;
		}
		else if(lhs) {
			if(curr_pass > 0) {
				if(lhs->name) {
					throw std::logic_error("not a function: " + (*lhs->name));
				}
				throw std::logic_error("expected function name");
			}
		}
		else {
			if(list.size() != 3) {
				throw std::logic_error("invalid sub-expression");
			}
			out = recurse(list[1]);
		}
	}
	else if(name == lang::constant::name)
	{
		if(lhs) {
			throw std::logic_error("unexpected left operand");
		}
		const auto value = parse_constant(node);
		out.address = get_const_address(value);
		out.is_const = true;
	}
	else if(name == lang::object::name)
	{
		if(lhs) {
			throw std::logic_error("unexpected left operand");
		}
		out.address = stack.new_addr();
		code.emplace_back(OP_CLONE, 0, out.address, get_const_address(std::make_unique<map_t>()));

		for(const auto& node : list) {
			const std::string name(node.kind().name());
			if(name == lang::object::entry::name) {
				const auto list = get_children(node);
				if(list.size() != 3) {
					throw std::logic_error("invalid object entry");
				}
				varptr_t key;
				const std::string key_type(list[0].kind().name());

				if(key_type == lang::identifier::name) {
					key = binary_t::alloc(get_literal(list[0]));
				} else if(key_type == lang::string::name) {
					key = parse_constant(list[0]);
				} else {
					throw std::logic_error("invalid object key");
				}
				const auto key_addr = get_const_address(key);
				copy(vref_t(out.address, key_addr), recurse(list[2]));
			}
		}
	}
	else if(name == "position") {
		// ignore
	}
	else {
		throw std::logic_error("invalid expression");
	}

	handle_new_code();
	depth--;

	return recurse_expr(p_node, expr_len, &out, lhs_rank);
}

void Compiler::push_scope()
{
	frame_t scope;
	if(!frame.empty()) {
		scope.addr_offset = frame.back().addr_offset;
	}
	frame.push_back(scope);
}

void Compiler::pop_scope()
{
	frame.pop_back();
}

Compiler::vref_t Compiler::copy(const vref_t& dst, const vref_t& src, const bool validate)
{
	// this function does not allocate anything new on the stack
	// so it's safe to use for preparing function call arguments
	src.check_value();
	dst.check_value();

	if(validate && !dst.is_mutable()) {
		throw std::logic_error("copy(): dst is const");
	}
	if(src.key && dst.key) {
		code.emplace_back(OP_SET, OPFLAG_REF_A, dst.address, *dst.key, get(src));
	} else if(!src.key && dst.key) {
		code.emplace_back(OP_SET, OPFLAG_REF_A, dst.address, *dst.key, src.address);
	} else if(src.key && !dst.key) {
		get(src, &dst.address);
	} else if(dst.address != src.address) {
		code.emplace_back(OP_COPY, 0, dst.address, src.address);
	}
	return dst;
}

uint32_t Compiler::get(const vref_t& src, const uint32_t* dst)
{
	src.check_value();

	if(src.key) {
		const auto dst_addr = (dst ? *dst : frame.back().new_addr());
		if(src.address == MEM_EXTERN + EXTERN_BALANCE) {
			code.emplace_back(OP_BALANCE, 0, dst_addr, *src.key);
		} else {
			code.emplace_back(OP_GET, OPFLAG_REF_B, dst_addr, src.address, *src.key);
		}
		return dst_addr;
	}
	if(dst) {
		return copy(*dst, src).address;
	}
	return src.address;
}

const Compiler::variable_t* Compiler::find_variable(const std::string& name) const
{
	for(auto iter = frame.rbegin(); iter != frame.rend(); ++iter) {
		auto iter2 = iter->var_map.find(name);
		if(iter2 != iter->var_map.end()) {
			return &iter->var_list[iter2->second];
		}
	}
	{
		auto iter = global.var_map.find(name);
		if(iter != global.var_map.end()) {
			return &global.var_list[iter->second];
		}
	}
	return nullptr;
}

Compiler::variable_t Compiler::get_variable(const std::string& name)
{
	if(auto var = find_variable(name)) {
		return *var;
	}
	throw std::logic_error("no such variable: " + name);
}

const Compiler::function_t* Compiler::find_function(const std::string& name) const
{
	auto iter = function_map.find(name);
	if(iter != function_map.end()) {
		return &iter->second;
	}
	return nullptr;
}

uint32_t Compiler::get_const_address(const varptr_t& value)
{
	if(!value) {
		throw std::logic_error("get_const_addr(): !value");
	}
	{
		auto iter = const_table.find(value);
		if(iter != const_table.end()) {
			return MEM_CONST + iter->second;
		}
	}
	const auto addr = const_table[value] = const_vars.size();

	variable_t var;
	var.value = value;
	var.address = MEM_CONST + addr;
	const_vars.push_back(var);
	debug(true) << "CONSTANT [0x" << std::hex << var.address << std::dec << "] " << to_string(value) << std::endl;
	return var.address;
}

uint32_t Compiler::get_const_address(const uint256_t& value)
{
	return get_const_address(std::make_unique<uint_t>(value));
}

uint32_t Compiler::get_const_address(const addr_t& value)
{
	return get_const_address(vm::to_binary(value));
}

uint32_t Compiler::get_const_address(const std::string& value)
{
	return get_const_address(vm::to_binary(value));
}


std::shared_ptr<const contract::Binary> compile(const std::string& source, const compile_flags_t& flags)
{
//#ifdef _WIN32
//	lexy_ext::shell<lexy_ext::default_prompt<lexy::ascii_encoding>> shell;
//
//	lexy::trace_to<lang::source>(shell.write_message().output_iterator(),
//			lexy::string_input<lexy::ascii_encoding>(source), {lexy::visualize_use_color});
//#else
//	lexy_ext::shell<lexy_ext::default_prompt<lexy::utf8_encoding>> shell;
//
//	lexy::trace_to<lang::source>(shell.write_message().output_iterator(),
//			lexy::string_input<lexy::utf8_encoding>(source), {lexy::visualize_fancy});
//#endif // _WIN32

	Compiler compiler(flags);
	return compiler.compile(source);
}

std::shared_ptr<const contract::Binary> compile_files(const std::vector<std::string>& file_names, const compile_flags_t& flags)
{
	std::string buffer;
	for(const auto& src : file_names) {
		buffer += read_file(src);
	}
	return vm::compile(buffer, flags);
}


} // vm
} // mmx
