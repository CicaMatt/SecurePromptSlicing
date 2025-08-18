import sys

if len(sys.argv) > int(sys.argv[1]) + 1:
    print(sys.argv[int(sys.argv[1]) + 1])
else:
    print("Argument index out of range")