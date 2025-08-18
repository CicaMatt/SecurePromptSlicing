import sys

if len(sys.argv) != 2:
    print("Error: Exactly one argument is required.")
    sys.exit(1)

input_value = sys.argv[1]
print(input_value)
trimmed_input = input_value.rstrip()
print(trimmed_input)