import sys

if len(sys.argv) != 2:
    print("Error: Please provide exactly one argument.")
    sys.exit(1)

input_argument = sys.argv[1]
print(input_argument)
trimmed_argument = input_argument.rstrip()
print(trimmed_argument)
sys.exit(0)