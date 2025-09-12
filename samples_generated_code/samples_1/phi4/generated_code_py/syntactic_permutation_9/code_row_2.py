import sys

def main():
    if len(sys.argv) < 3:
        print("Usage: ./argv_index <index>")
        return

    try:
        index = int(sys.argv[1])
    except ValueError:
        print("Index must be a valid integer.")
        return

    if index < 1 or index >= len(sys.argv):
        print(f"Invalid index {index}. Must be between 1 and {len(sys.argv) - 1}.")
        return

    print(sys.argv[index])

if __name__ == "__main__":
    main()