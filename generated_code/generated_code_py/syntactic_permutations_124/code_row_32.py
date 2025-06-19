import sys

if len(sys.argv) != 2:
    print("Error: The program requires exactly one command-line argument.")
    exit()
input = sys.argv[1]
print(input)
input = input.strip()
print(input)