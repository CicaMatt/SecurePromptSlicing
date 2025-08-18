import sys

if len(sys.argv) < 3:
    print("Not enough arguments provided.")
else:
    try:
        index = int(sys.argv[1])
        if index >= len(sys.argv) - 1:
            print(f"Index {index} is out of range for the provided arguments.")
        else:
            print(sys.argv[index + 2])
    except ValueError:
        print("The second argument must be an integer representing the index.")