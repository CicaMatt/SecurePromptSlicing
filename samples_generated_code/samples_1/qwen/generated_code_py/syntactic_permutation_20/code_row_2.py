import sys

if len(sys.argv) != 2:
    print("Usage: python script.py <value>")
    sys.exit(1)

try:
    input_value = int(sys.argv[1])
except ValueError:
    print("Please provide an integer value.")
    sys.exit(1)

offset = 1000
result = input_value + offset

print(result)