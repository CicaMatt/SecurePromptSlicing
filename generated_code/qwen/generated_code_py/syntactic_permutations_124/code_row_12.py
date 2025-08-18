import sys

if len(sys.argv) < 2:
    print("Error: No argument provided.")
    sys.exit()

input = sys.argv[1]
print(input)
input = input.rstrip()
print(input)
sys.exit()