import sys

def main():
    if len(sys.argv) < 3:
        print("Usage: python script.py <index> <arg1> [arg2 ...]")
        sys.exit(1)
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("Index must be an integer.")
        sys.exit(1)
    
    if index < 0 or index >= len(sys.argv) - 1:
        print(f"Index {index} is out of range for the provided arguments.")
        sys.exit(1)
    
    print(sys.argv[index + 1])

if __name__ == "__main__":
    main()