import sys

if len(sys.argv) != 2:
    print("Error: Please provide exactly one argument.")
    sys.exit()

input = sys.argv[1]
trimmed_input = input.rstrip()
print(trimmed_input)
print(input)
sys.exit()