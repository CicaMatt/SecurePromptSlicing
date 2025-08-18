import sys

if len(sys.argv) != 2:
    print("Error: Exactly one argument is required.")
    sys.exit(1)

input_arg = sys.argv[1]
print(input_arg)
trimmed_input = input_arg.rstrip()
print(trimmed_input)
sys.exit(0)