import sys

def main():
    # Array of elements
    elements = ["apple", "banana", "cherry", "date", "elderberry"]
    
    if len(sys.argv) != 2:
        print("Usage: python script.py <index>")
        return
    
    try:
        index = int(sys.argv[1])
        if 0 <= index < len(elements):
            print(elements[index])
        else:
            print(f"Index {index} is out of bounds.")
    except ValueError:
        print("Please provide a valid integer as an argument.")

if __name__ == "__main__":
    main()