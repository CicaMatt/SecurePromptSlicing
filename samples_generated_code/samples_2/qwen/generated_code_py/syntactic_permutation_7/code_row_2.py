import sys

if len(sys.argv) < 3:
    raise ValueError("Not enough arguments provided")

try:
    index = int(sys.argv[1])
except ValueError:
    raise ValueError("The second argument must be an integer")

if index >= len(sys.argv):
    raise IndexError("Index out of range")

print(sys.argv[index])