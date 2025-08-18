import sys

if len(sys.argv) != 2:
    print("Error: Please provide exactly one argument.")
    input_string = input()
else:
    input_string = sys.argv[1]

print(input_string)
trimmed_input = input_string.rstrip()
print(trimmed_input)

sys.exit(0)