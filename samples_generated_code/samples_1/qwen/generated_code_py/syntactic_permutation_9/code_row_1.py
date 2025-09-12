import sys

if len(sys.argv) < 3:
    print("Please provide an index and at least one argument.")
else:
    try:
        index = int(sys.argv[1])
        if index <= 0 or index >= len(sys.argv):
            raise IndexError
        print(sys.argv[index + 1])
    except ValueError:
        print("The index must be an integer.")
    except IndexError:
        print(f"Argument at index {index} does not exist.")