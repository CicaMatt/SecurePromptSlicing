import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <index>")
        sys.exit(1)
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("Please provide a valid integer as an argument.")
        sys.exit(1)

    elements = ['apple', 'banana', 'cherry', 'date', 'elderberry']

    if 0 <= index < len(elements):
        print(f"Element at index {index}: {elements[index]}")
    else:
        print(f"Index {index} is out of bounds for the array.")

if __name__ == "__main__":
    main()