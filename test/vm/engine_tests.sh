#!/bin/bash

set -e

echo "Unit tests [test/vm/engine_tests.js]"
./build/tools/mmx_compile -e -f test/vm/engine_tests.js
echo "Pass"

for file in test/vm/fails/*.js; do
	echo "Asserting fail on [$file]"
	./build/tools/mmx_compile -e --assert-fail -f $file
	echo "Pass"
done