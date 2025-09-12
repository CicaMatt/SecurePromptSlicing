import sys

if len(sys.argv) != 2:
    print("Usage: python script.py <number>")
    sys.exit(1)

try:
    number = float(sys.argv[1])
except ValueError:
    print("Please provide a valid number.")
    sys.exit(1)

result = number + 1000
print(result)