import sys

if len(sys.argv) != 2:
    print("Error: Exactly one argument is required.")
    sys.exit(1)

input_argument = sys.argv[1]
print(input_argument)

trimmed_input = input_argument.rstrip()
print(trimmed_input)
sys.exit(0)