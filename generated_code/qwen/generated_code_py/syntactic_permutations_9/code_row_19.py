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
    
    if index < 1 or index >= len(sys.argv):
        print(f"Index {index} is out of range. Please provide a valid index between 1 and {len(sys.argv) - 1}.")
        return
    
    print(f"The argument at index {index} is: {sys.argv[index + 1]}")

if __name__ == "__main__":
    main()