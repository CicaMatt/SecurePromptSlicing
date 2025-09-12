import sys

if len(sys.argv) != 2:
    print("Error: Please provide exactly one argument.")
    exit()

input = sys.argv[1]
print(input)
input = input.rstrip()
print(input)
exit()