#!/bin/bash

echo ""
echo "======================================================"
echo "     BUILDING"
echo "======================================================"
echo ""
# rm -rf build
# cmake -B build -DCMAKE_BUILD_TYPE=Debug
# cmake --build build

echo ""
echo "======================================================"
echo "     UNIT TESTS"
echo "======================================================"
echo ""
# ./build/test/unit_tests/cppfetch_unit_tests

echo ""
echo "======================================================"
echo "     MEMORY TESTS"
echo "======================================================"
# valgrind \
# --tool=memcheck \
# --leak-check=full \
# --show-leak-kinds=all \
# --gen-suppressions=yes \
# --track-origins=yes \
# --suppressions=test/valgrind.supp \
# ./build/examples/cppfetch_example_single

echo ""
echo "======================================================"
echo "     THREADING TESTS"
echo "======================================================"
valgrind \
--tool=helgrind \
--gen-suppressions=yes \
--suppressions=test/valgrind.supp \
./build/test/other_tests/cppfetch_other_tests
