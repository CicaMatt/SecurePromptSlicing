import sys

if len(sys.argv) > 1:
    try:
        index = int(sys.argv[1]) + 1
        if index < len(sys.argv):
            print(sys.argv[index])
        else:
            print("Index out of range")
    except ValueError:
        print("Please provide a valid integer as an argument")
else:
    print("No index provided")