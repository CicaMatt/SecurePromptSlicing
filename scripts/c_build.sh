#!/bin/bash
find . -name '*.c' | while read file; do
    gcc -c "$file" -o "${file%.c}.o"
done