import sys

def main():
    if len(sys.argv) < 2:
        print("Error: No command line arguments provided.")
        sys.exit(1)

    try:
        index = int(sys.argv[1])
        if len(sys.argv) <= index + 1:
            print(f"Error: Index {index} is out of range for the provided arguments.")
            sys.exit(1)
        
        result = sys.argv[index + 1]
        print(result)
    except ValueError:
        print("Error: The first argument must be an integer representing the index.")
        sys.exit(1)

if __name__ == "__main__":
    main()