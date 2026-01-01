#!/bin/bash
set -xe

# Validate input
if [ -z "$1" ]; then
    echo "Usage: $0 <number>"
    exit 1
fi

x="$1"
dir="day$x"

mkdir -p "$dir"

touch \
    "$dir/day${x}a.cpp" \
    "$dir/day${x}b.cpp" \
    "$dir/day${x}.txt" \
    "$dir/test.txt" \
    "$dir/build.sh"

cat > "$dir/build.sh" << EOF
#!/bin/bash
set -xe

clang++ --std=c++20 -Wall -Wextra -Werror -O2 day${x}a.cpp -o day${x}a
# clang++ --std=c++20 -Wall -Wextra -Werror -O2 day${x}b.cpp -o day${x}b
EOF

chmod +x "$dir/build.sh"
