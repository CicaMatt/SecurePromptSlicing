import sys

def main():
    if len(sys.argv) < 3:
        print("Usage: ./argv_index index")
        sys.exit(1)
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("The first argument must be an integer representing the index.")
        sys.exit(1)

    if index < 0 or index >= len(sys.argv) - 1:
        print(f"Index out of range. Please provide an index between 0 and {len(sys.argv) - 2}.")
        sys.exit(1)
    
    print(sys.argv[index + 1])

if __name__ == "__main__":
    main()