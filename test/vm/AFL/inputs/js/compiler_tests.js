
null;

{
	var test;
	if(test != null) {
		fail("empty var");
	}
}

function test1(a, b = 1) {
	return a + b;
}

if(test1(1) != 2) {
	fail("test1");
}

if(concat(to_string(1), to_string(2), to_string(3)) != "123") {
	fail("concat()", 1);
}

{
	var map = {};
	if(map.test != null) {
		fail("map.test != null");
	}
}
{
	var map = {};
	map.tmp = 123;
	if(map.tmp != 123) {
		fail("var to key assignment");
	}
}
{
	var map = {"test": 123};
	const tmp = map.test;
	if(tmp != 123) {
		fail("key to var assignment");
	}
	map.tmp = map.test;
	if(map.tmp != 123) {
		fail("key to key assignment");
	}
}

if(balance() != 0) {
	fail("balance() != 0");
}
if(balance(sha256("test")) != 0) {
	fail("balance(test) != 0");
}
if(this.balance[bech32()] != 0) {
	fail("this.balance != 0");
}
{
	var tmp = balance();
	if(tmp != 0) {
		fail("balance() != 0");
	}
	tmp = 1337;
}
{
	var tmp = this.balance[bech32()];
	if(tmp != 0) {
		fail("this.balance != 0");
	}
	tmp = 1337;
}

{
	var array = [1, 2, 3];
	for(var entry of array) {
		entry = 0;
	}
	for(const entry of array) {
		if(entry == 0) {
			fail("var entry of array (integer)");
		}
	}
}
{
	var array = ["1", "2", "3"];
	for(var entry of array) {
		entry = "0";
	}
	for(const entry of array) {
		if(entry == "0") {
			fail("var entry of array (string)");
		}
	}
}
{
	var array = [[1], [2], [3]];
	for(var entry of array) {
		entry = [];
	}
	for(const entry of array) {
		if(size(entry) == 0) {
			fail("var entry of array (array)");
		}
	}
}
{
	var array = [{val: 1}, {val: 2}, {val: 3}];
	for(var entry of array) {
		entry = {val: 0};
	}
	for(const entry of array) {
		if(entry.val == 0) {
			fail("var entry of array (object)");
		}
	}
}

{
	var obj = {key: "value"};
	if(obj.key != "value") {
		fail("object key (1)");
	}
}
{
	var obj = {"key": "value"};
	if(obj.key != "value") {
		fail("object key (2)");
	}
}
{
	var obj = {test: 123, key: "value"};
	if(obj.key != "value") {
		fail("object key (3)");
	}
}
{
	var obj = { key : "value" };
	if(obj.key != "value") {
		fail("object key (4)");
	}
}
{
	var obj = { 	key		 : 	"value" };
	if(obj.key != "value") {
		fail("object key (5)");
	}
}
{
	var obj = {_key_: "value"};
	if(obj._key_ != "value") {
		fail("object _key_");
	}
}

if(1337 / 16 != 83) {
	fail("1337 / 16 != 83");
}
if(1337 % 16 != 9) {
	fail("1337 % 16 != 9");
}
if(1337133713371337 / 1024 != 1305794641964) {
	fail("1337133713371337 / 1024 != 1305794641964");
}
if(1337133713371337 % 1024 != 201) {
	fail("1337133713371337 % 1024 != 201");
}

if(false) {
	fail("if(false)");
}
if(!true) {
	fail("if(!true)");
}
if(1 == 2) {
	fail("if(1 == 2)");
}
if(1 != 1) {
	fail("if(1 != 1)");
}
if(2 < 1) {
	fail("if(2 < 1)");
}
if(1 > 2) {
	fail("if(1 > 2)");
}
if(2 <= 1) {
	fail("if(2 <= 1)");
}
if(1 >= 2) {
	fail("if(1 >= 2)");
}
if(!(1 == 1)) {
	fail("if(!(1 == 1))");
}
if((1 == 1) && (1 == 0)) {
	fail("if((1 == 1) && (1 == 0))");
}
if((1 != 1) || (1 != 1)) {
	fail("if((1 != 1) || (1 != 1))");
}
if(0) {
	fail("if(0)");
}
if(null) {
	fail("if(null)");
}
if("") {
	fail("if('')");
}
if(!1337) {
	fail("if(!1337)");
}
if(!"test") {
	fail("if(!'test')");
}
if(!(true && 1337 && "test")) {
	fail("if(!(1 && true && 'test'))");
}
if(0 || null || "") {
	fail("if(0 || null || '')");
}
if(!(0 || null || 1)) {
	fail("if(!(null || null || 1))");
}
{
	var cond = (1 > 2);
	if(cond) {
		fail("if(cond)");
	}
}
{
	const cond = (1 > 2);
	if(cond) {
		fail("if(cond)");
	}
}



