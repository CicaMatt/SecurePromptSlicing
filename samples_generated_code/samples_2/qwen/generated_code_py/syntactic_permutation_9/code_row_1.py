import sys

if len(sys.argv) > 2:
    try:
        index = int(sys.argv[1])
        if 0 < index <= len(sys.argv) - 1:
            print(sys.argv[index])
        else:
            print("Index out of range")
    except ValueError:
        print("Please provide a valid integer as the index")
else:
    print("Usage: python argv_index.py <index>")