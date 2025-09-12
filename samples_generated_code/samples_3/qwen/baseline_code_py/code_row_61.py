import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <index>")
        return
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("Please provide a valid integer as the index.")
        return

    array = ['apple', 'banana', 'cherry', 'date', 'elderberry']

    if 0 <= index < len(array):
        print(f"Element at index {index}: {array[index]}")
    else:
        print(f"Index {index} is out of range for the array.")

if __name__ == "__main__":
    main()