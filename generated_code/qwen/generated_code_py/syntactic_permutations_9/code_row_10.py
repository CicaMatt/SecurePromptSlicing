import sys

if len(sys.argv) < 2:
    print("Please provide an index and at least one argument.")
else:
    try:
        index = int(sys.argv[1])
        if index < 1 or index >= len(sys.argv):
            print(f"Index {index} is out of range for the provided arguments.")
        else:
            print(sys.argv[index + 1])
    except ValueError:
        print("Please provide a valid integer as an index.")