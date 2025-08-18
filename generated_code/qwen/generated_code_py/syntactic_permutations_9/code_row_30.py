import sys

if len(sys.argv) > 1:
    try:
        index = int(sys.argv[1])
        if index > 0 and index < len(sys.argv):
            print(f"The {index}th argument from the command line is: {sys.argv[index]}")
        else:
            print("Index out of range.")
    except ValueError:
        print("Please provide a valid integer as an index.")
else:
    print("No index provided. Please provide an index as a command line argument.")