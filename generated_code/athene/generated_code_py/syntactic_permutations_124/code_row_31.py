import sys

if len(sys.argv) != 2:
    print("Error: You must provide exactly one argument.")
    sys.exit(1)

input = sys.argv[1]
print(input)
print(input.rstrip())

sys.exit(0)