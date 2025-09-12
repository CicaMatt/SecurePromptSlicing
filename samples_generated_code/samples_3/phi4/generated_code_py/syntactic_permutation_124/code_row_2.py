import sys

if len(sys.argv) < 2:
    print("Error: No argument provided.")
    sys.exit(1)

input_arg = sys.argv[1]

print(input_arg)
trimmed_input_arg = input_arg.rstrip()
print(trimmed_input_arg)
sys.exit(0)