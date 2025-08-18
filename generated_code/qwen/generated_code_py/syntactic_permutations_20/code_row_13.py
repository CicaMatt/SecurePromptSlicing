import sys

if len(sys.argv) != 2:
    print("Please provide exactly one argument.")
    sys.exit(1)

try:
    input_value = int(sys.argv[1])
except ValueError:
    print("The provided argument must be an integer.")
    sys.exit(1)

offset = 1000
result = input_value + offset

print(result)