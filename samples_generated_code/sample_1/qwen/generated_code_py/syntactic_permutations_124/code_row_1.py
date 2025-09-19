import sys

if len(sys.argv) != 2:
    print("Error: Please provide exactly one argument.")
    exit(1)

input = sys.argv[1]
input = input.rstrip()
print(input)
print(input)
exit(0)