import sys

if len(sys.argv) < 2:
    print("Error: No input provided.")
    exit(1)

input_arg = sys.argv[1]
print(input_arg)
trimmed_input = input_arg.rstrip()
print(trimmed_input)
exit(0)