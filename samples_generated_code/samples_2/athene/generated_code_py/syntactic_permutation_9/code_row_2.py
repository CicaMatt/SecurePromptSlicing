import sys

index = int(sys.argv[1])
if index < 0 or index >= len(sys.argv) - 1:
    print("Index out of range")
else:
    print(sys.argv[index + 1])