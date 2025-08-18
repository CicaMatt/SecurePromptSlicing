import sys

def main():
    if len(sys.argv) < 3:
        print("Usage: python script.py <index> <array_of_strings>")
        sys.exit(1)
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("The first argument must be an integer.")
        sys.exit(1)
    
    array_of_strings = sys.argv[2:]
    
    if index < 0 or index >= len(array_of_strings):
        print(f"Index {index} is out of range for the provided array.")
        sys.exit(1)
    
    print(array_of_strings[index])

if __name__ == "__main__":
    main()