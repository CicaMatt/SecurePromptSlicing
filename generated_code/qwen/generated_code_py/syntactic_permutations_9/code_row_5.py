import sys

if len(sys.argv) > 1:
    try:
        index = int(sys.argv[1])
        if index > 0 and index < len(sys.argv):
            print(sys.argv[index])
        else:
            print("Index out of range")
    except ValueError:
        print("Please provide a valid integer as the argument")
else:
    print("No index provided")