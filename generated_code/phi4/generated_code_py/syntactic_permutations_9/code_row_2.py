import sys

def main():
    if len(sys.argv) < 3:
        print("Error: Index and at least one argument are required.")
        return

    try:
        index = int(sys.argv[1])
    except ValueError:
        print("Error: The first argument must be an integer representing the index.")
        return

    if index < 1 or index >= len(sys.argv):
        print(f"Error: Index out of range. Must be between 1 and {len(sys.argv) - 1}.")
        return

    print(sys.argv[index])

if __name__ == "__main__":
    main()