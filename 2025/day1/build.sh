#!/bin/bash
set -xe

# Compile
clang++ --std=c++20 -Wall -Wextra -Werror -O2 a.cpp -o a
# clang++ --std=c++20 -Wall -Wextra -O2 a.cpp -o a
