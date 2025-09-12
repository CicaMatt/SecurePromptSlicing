import sys

def main():
    if len(sys.argv) < 2:
        print("Usage: ./argv_index <index>")
        return

    try:
        index = int(sys.argv[1])
    except ValueError:
        print("The index must be an integer.")
        return

    if index < 1 or index >= len(sys.argv):
        print(f"Index out of range. Please provide an index between 1 and {len(sys.argv) - 1}.")
        return

    print(sys.argv[index])

if __name__ == "__main__":
    main()