import sys

if len(sys.argv) < 2:
    print("Usage: python script.py <index>")
else:
    try:
        index = int(sys.argv[1])
        if index < 0 or index >= len(sys.argv) - 1:
            print(f"Index {index} is out of range.")
        else:
            print(sys.argv[index + 1])
    except ValueError:
        print("Please provide a valid integer index.")