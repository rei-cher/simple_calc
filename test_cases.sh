#!/usr/bin/env bash

set -u

BIN="${1:-./build/simplecalc}"

passed=0
failed=0
test_number=0

run_test()
{
    local description="$1"
    local expected_exit="$2"
    shift 2

    local actual_exit

    test_number=$((test_number + 1))

    "$BIN" "$@" >/dev/null 2>&1
    actual_exit=$?

    if ((expected_exit == actual_exit))
    then
        printf "PASS %02d: %s\n" "$test_number" "$description"
        passed=$((passed + 1))
    else
        printf "FAIL %02d: %s\n" "$test_number" "$description"
        printf "  Command: %q" "$BIN"
        printf " %q" "$@"
        printf "\n"
        printf "  Expected exit: %d\n" "$expected_exit"
        printf "  Actual exit:   %d\n" "$actual_exit"

        failed=$((failed + 1))
    fi
}

if [[ ! -x "$BIN" ]]
then
    printf "Error: executable not found: %s\n" "$BIN"
    exit 2
fi

# Successful arithmetic
run_test "addition"									  0 "10" "+" "20"
run_test "negative addition"						  0 "-10" "+" "-20"
run_test "subtraction"								  0 "10" "-" "5"
run_test "multiplication"							  0 "6" "*" "7"
run_test "division"									  0 "10" "/" "3"
run_test "modulo"									  0 "10" "%" "3"

# Arithmetic errors
run_test "addition overflow"						  1 "2147483647" "+" "1"
run_test "addition underflow"						  1 "-2147483648" "+" "-1"
run_test "subtraction overflow"						  1 "2147483647" "-" "-1"
run_test "subtraction underflow"					  1 "-2147483648" "-" "1"
run_test "multiplication overflow"					  1 "2147483647" "*" "2"
run_test "division by zero"							  1 "10" "/" "0"
run_test "division overflow"						  1 "-2147483648" "/" "-1"
run_test "modulo by zero"							  1 "10" "%" "0"

# Successful bitwise operations
run_test "bitwise AND"								  0 "255" "&" "15"
run_test "bitwise OR"								  0 "240" "|" "15"
run_test "bitwise XOR"								  0 "170" "^" "85"
run_test "left shift"								  0 "8" "<<" "2"
run_test "right shift"								  0 "16" ">>" "2"
run_test "left rotate"								  0 "2147483649" "<<<" "1"
run_test "right rotate"								  0 "1" ">>>" "1"

# Shift errors
run_test "invalid left shift"						  1 "1" "<<" "32"
run_test "invalid right shift"						  1 "1" ">>" "32"

# Signed input validation
run_test "signed above INT32_MAX"					  1 "2147483648" "+" "0"
run_test "signed below INT32_MIN"					  1 "-2147483649" "+" "0"
run_test "invalid signed input"						  1 "12abc" "+" "5"
run_test "floating-point input"       				  1 "12.5" "+" "5"
run_test "empty signed input"         				  1 "" "+" "5"

# Unsigned input validation
run_test "maximum uint32 value"       				  0 "4294967295" "|" "0"
run_test "unsigned above UINT32_MAX"  				  1 "4294967296" "|" "0"
run_test "negative unsigned input"    				  1 "-1" "&" "1"

# Operator and argument validation
run_test "invalid operator"           				  1 "10" "@" "5"
run_test "missing operand"            				  1 "10" "+"
run_test "too many arguments"         				  1 "10" "+" "5" "extra"
run_test "invalid first integer (combined string)"	  1 "10,Some string" "+" "5"
run_test "invalid second integer (combined string)"	  1 "10" "+" "5,Some string"

printf "\nPassed: %d\n" "$passed"
printf "Failed: %d\n" "$failed"
printf "Total:  %d\n" "$test_number"

if ((0 == failed))
then
    exit 0
else
    exit 1
fi
