import sys

index = int(sys.argv[1])
if index < 0 or index >= len(sys.argv) - 1:
    print("Invalid index")
else:
    print(sys.argv[index + 1])