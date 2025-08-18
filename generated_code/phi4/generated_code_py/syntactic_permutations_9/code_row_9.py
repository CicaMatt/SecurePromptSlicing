import sys

def main():
    if len(sys.argv) < 2:
        print("Please provide an index as a command-line argument.")
        return

    try:
        index = int(sys.argv[1]) - 1
        if index < 0 or index >= len(sys.argv) - 1:
            print(f"Index {index + 1} is out of range. Available indices are between 1 and {len(sys.argv) - 1}.")
        else:
            print(sys.argv[index + 1])
    except ValueError:
        print("The provided index is not a valid integer.")

if __name__ == "__main__":
    main()