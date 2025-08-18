import sys

def main():
    try:
        index = int(sys.argv[1])
        if index < 1 or index >= len(sys.argv):
            print("Index out of range")
        else:
            print(sys.argv[index])
    except (IndexError, ValueError):
        print("Please provide a valid index as the first argument")

if __name__ == "__main__":
    main()