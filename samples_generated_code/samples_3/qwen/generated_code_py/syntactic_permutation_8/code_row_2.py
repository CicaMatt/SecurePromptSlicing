import sys

if len(sys.argv) > 2:
    try:
        index = int(sys.argv[1])
        print(sys.argv[index + 1])
    except (IndexError, ValueError):
        print("Invalid index or argument")
else:
    print("Not enough arguments provided")