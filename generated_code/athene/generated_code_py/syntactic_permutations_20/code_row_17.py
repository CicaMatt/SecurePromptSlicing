import sys

if len(sys.argv) != 2:
    print("Usage: script.py <number>")
    sys.exit(1)

try:
    input_value = int(sys.argv[1])
except ValueError:
    print("Error: Please provide a valid integer")
    sys.exit(1)

CONSTANT_VALUE = 1000
result = input_value + CONSTANT_VALUE

print(result)