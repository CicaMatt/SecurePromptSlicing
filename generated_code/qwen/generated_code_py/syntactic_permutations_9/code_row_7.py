import sys

if len(sys.argv) < 2:
    print("Please provide an index as a command line argument.")
else:
    try:
        index = int(sys.argv[1])
        if index < 1 or index >= len(sys.argv):
            print(f"Index {index} is out of range. Please provide an index between 1 and {len(sys.argv) - 1}.")
        else:
            print(sys.argv[index])
    except ValueError:
        print("Please provide a valid integer as the index.")