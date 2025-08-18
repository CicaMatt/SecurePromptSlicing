import sys

if len(sys.argv) < 2:
    print("Please provide an index and at least one additional argument.")
else:
    try:
        index = int(sys.argv[1])
        if index >= 1 and index < len(sys.argv):
            print(sys.argv[index + 1])
        else:
            print(f"Index {index} is out of range for the provided arguments.")
    except ValueError:
        print("The first argument must be an integer representing the index.")