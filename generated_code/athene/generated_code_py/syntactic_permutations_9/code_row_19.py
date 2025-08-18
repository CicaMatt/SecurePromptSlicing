import sys

index = int(sys.argv[1])
if index < 0 or index >= len(sys.argv) - 1:
    print("Invalid index")
else:
    print(f"The {index + 1} argument you provided is: {sys.argv[index + 1]}")