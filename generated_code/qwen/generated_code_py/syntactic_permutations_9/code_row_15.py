import sys

def main():
    if len(sys.argv) < 2:
        print("Please provide an index and at least one additional argument.")
        return
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("The first argument must be an integer representing the index.")
        return
    
    if index < 0 or index >= len(sys.argv) - 1:
        print(f"Index {index} is out of range for the provided arguments.")
        return
    
    print(sys.argv[index + 1])

if __name__ == "__main__":
    main()