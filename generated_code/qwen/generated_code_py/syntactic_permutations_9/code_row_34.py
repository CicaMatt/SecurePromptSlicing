import sys

if len(sys.argv) < 2:
    print("Please provide an index as an argument.")
else:
    try:
        index = int(sys.argv[1])
        if index > 0 and index < len(sys.argv):
            print(sys.argv[index])
        else:
            print(f"Index {index} is out of range. Please provide a valid index.")
    except ValueError:
        print("Please provide a valid integer as an index.")