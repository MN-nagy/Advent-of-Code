#!/bin/bash
set -xe

# Compile
clang++ --std=c++20 -Wall -Wextra -Werror -O2 day4b.cpp -o day4b
# clang++ --std=c++20 -Wall -Wextra -O2 a.cpp -o a
