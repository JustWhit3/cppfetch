#!/bin/bash

# Variables
declare -a source_files=(
  "core.cpp"
  "utils.cpp"
)

# Source code check
echo ""
echo "======================================================"
echo "     IWYU Checks"
echo "======================================================"
echo ""
for source in "${source_files[@]}"; do
  include-what-you-use \
    -std=c++20 \
    -I/usr/lib/llvm-14/lib/clang/14.0.0/include \
    -Iinclude \
    src/"$source"

  echo ""
  echo "--------------------------------------------------"
  echo ""
done