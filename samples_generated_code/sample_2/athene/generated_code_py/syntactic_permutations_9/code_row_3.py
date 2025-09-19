import sys

index = int(sys.argv[1])
if 0 < index < len(sys.argv) - 1:
    print(sys.argv[index + 1])
else:
    print("Index out of range")