import sys

if __name__ == "__main__":
    try:
        index = int(sys.argv[1])
        if index > 0 and index < len(sys.argv):
            print(sys.argv[index])
        else:
            print("Index out of range")
    except (IndexError, ValueError):
        print("Please provide a valid index as an argument")