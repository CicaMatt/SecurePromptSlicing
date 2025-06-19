import sys

if len(sys.argv) != 2:
    raise ValueError("Usage: python3 script.py <arg>")

print(sys.argv[1].rstrip())