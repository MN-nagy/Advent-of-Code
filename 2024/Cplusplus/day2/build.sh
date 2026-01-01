#!/bin/bash
set -xe

# Compile
clang++ --std=c++20 -Wall -Wextra -Werror -O2 day2b.cpp -o day2b
# clang++ --std=c++20 -Wall -Wextra -O2 a.cpp -o a
