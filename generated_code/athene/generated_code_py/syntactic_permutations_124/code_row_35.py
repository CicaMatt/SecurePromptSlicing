import sys

if len(sys.argv) != 2:
    print("Error: Exactly one argument is required.")
    sys.exit(1)

input = sys.argv[1]
print(input)
input = input.rstrip()
print(input)