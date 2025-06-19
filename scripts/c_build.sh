#!/bin/bash
find . -name "*.c" | while read file; do
    gcc -c "$file" -o "${file%.c}.o" 2>/dev/null || true
done