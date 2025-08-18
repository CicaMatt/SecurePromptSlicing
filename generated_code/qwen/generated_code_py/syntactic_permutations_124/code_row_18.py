import sys

if len(sys.argv) != 2:
    print("Error: Please provide exactly one argument.")
    input = input("Enter the argument: ")
else:
    input = sys.argv[1]

print(input)
input = input.rstrip()
print(input)
sys.exit()