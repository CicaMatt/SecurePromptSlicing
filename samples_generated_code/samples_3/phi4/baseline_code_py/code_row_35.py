import sys

def main():
    if len(sys.argv) < 3:
        print("Usage: python argv_index.py <index>")
        sys.exit(1)

    try:
        index = int(sys.argv[1])
        if 0 < index < len(sys.argv):
            print(sys.argv[index])
        else:
            print(f"Argument at position {index} does not exist. Please provide a valid index.")
    except ValueError:
        print("The provided index is not an integer.")

if __name__ == "__main__":
    main()