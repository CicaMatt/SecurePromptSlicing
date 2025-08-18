import sys

if len(sys.argv) < 2:
    print("Please provide an index and at least one additional argument.")
else:
    try:
        index = int(sys.argv[1])
        if index < 1 or index >= len(sys.argv):
            print(f"Index {index} is out of range. Please provide a valid index.")
        else:
            print(sys.argv[index + 1])
    except ValueError:
        print("The first argument must be an integer representing the index.")