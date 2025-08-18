import sys

if len(sys.argv) != 3:
    print("Usage: python script.py <index> <element1,element2,...>")
else:
    try:
        index = int(sys.argv[1])
        elements = sys.argv[2].split(',')
        if 0 <= index < len(elements):
            print(elements[index])
        else:
            print(f"Index {index} is out of range.")
    except ValueError:
        print("Please provide a valid integer for the index and a comma-separated list of elements.")