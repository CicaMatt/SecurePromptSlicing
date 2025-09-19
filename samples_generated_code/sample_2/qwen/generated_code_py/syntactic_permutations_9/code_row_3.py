import sys

if len(sys.argv) > 1:
    try:
        index = int(sys.argv[1])
        if index >= 1 and index < len(sys.argv):
            print(sys.argv[index + 1])
        else:
            print("Index out of range")
    except ValueError:
        print("Please provide a valid integer as an index")
else:
    print("No index provided")