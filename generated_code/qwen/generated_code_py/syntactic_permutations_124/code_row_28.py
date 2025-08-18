import sys

if len(sys.argv) != 2:
    print("Error: Please provide exactly one argument.")
    sys.exit()

input = sys.argv[1]
input = input.rstrip()
print(input)
sys.exit()