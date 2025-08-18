import sys

def main():
    if len(sys.argv) < 2:
        print("Usage: python script.py index")
        return
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("The provided index must be an integer.")
        return

    if index < 0 or index >= len(sys.argv):
        print(f"Index {index} is out of bounds. Please provide a valid index.")
        return
    
    # Print the argument at the given index (1-based)
    print(sys.argv[index + 1])

if __name__ == "__main__":
    main()