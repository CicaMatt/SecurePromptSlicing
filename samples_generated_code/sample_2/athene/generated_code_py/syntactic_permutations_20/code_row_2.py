import sys

if len(sys.argv) != 2:
    print("Usage: python script.py <number>")
    sys.exit(1)

try:
    input_value = int(sys.argv[1])
except ValueError:
    print("Error: Please enter a valid integer.")
    sys.exit(1)

OFFSET = 1000
result = input_value + OFFSET

print(result)