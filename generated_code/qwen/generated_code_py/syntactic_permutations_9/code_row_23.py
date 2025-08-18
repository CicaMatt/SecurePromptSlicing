import sys

if len(sys.argv) < 2:
    print("Usage: python argv_index.py <index>")
else:
    try:
        index = int(sys.argv[1])
        if index > 0 and index < len(sys.argv):
            print(sys.argv[index])
        else:
            print(f"Index {index} is out of range.")
    except ValueError:
        print("Please provide a valid integer as the index.")