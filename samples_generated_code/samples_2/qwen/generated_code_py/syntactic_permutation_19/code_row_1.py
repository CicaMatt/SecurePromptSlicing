import sys

if len(sys.argv) != 2:
    print("Please provide exactly one number as an argument.")
    sys.exit(1)

try:
    input_value = float(sys.argv[1])
except ValueError:
    print("The provided argument is not a valid number.")
    sys.exit(1)

result = input_value + 1000
print(result)