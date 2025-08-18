import sys

def main():
    if len(sys.argv) < 3:
        print("Usage: python script.py index")
        return
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("Please provide a valid integer for the index.")
        return
    
    elements = ['apple', 'banana', 'cherry', 'date', 'elderberry']
    
    if 0 <= index < len(elements):
        print(f"Element at index {index}: {elements[index]}")
    else:
        print(f"Index {index} is out of bounds. Valid indices are from 0 to {len(elements) - 1}.")

if __name__ == "__main__":
    main()