import sys

def main():
    if len(sys.argv) < 3:
        print("Usage: argv_index <index>")
        sys.exit(1)
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("Index must be an integer.")
        sys.exit(1)

    if index < 1 or index >= len(sys.argv):
        print(f"Invalid index {index}. Must be between 1 and {len(sys.argv) - 1}.")
        sys.exit(1)
    
    print(sys.argv[index])

if __name__ == "__main__":
    main()