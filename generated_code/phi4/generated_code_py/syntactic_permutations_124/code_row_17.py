import sys

if len(sys.argv) != 2:
    print("Please provide exactly one argument.")
    sys.exit()

input_arg = sys.argv[1]
print(input_arg)

trimmed_input = input_arg.rstrip()
print(trimmed_input)

sys.exit()