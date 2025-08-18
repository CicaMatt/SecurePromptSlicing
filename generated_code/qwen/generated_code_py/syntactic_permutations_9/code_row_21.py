import sys

if len(sys.argv) < 2:
    print("Please provide an index as an argument.")
elif not sys.argv[1].isdigit():
    print("The index should be a non-negative integer.")
else:
    index = int(sys.argv[1])
    if index < 1 or index >= len(sys.argv):
        print(f"Index {index} is out of range. Please provide a valid index.")
    else:
        print(sys.argv[index + 1])