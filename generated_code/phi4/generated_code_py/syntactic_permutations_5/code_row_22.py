import sys

def main():
    if len(sys.argv) != 3:
        print("Usage: python script.py <array_index>")
        return
    
    array = ['apple', 'banana', 'cherry', 'date', 'elderberry']
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("The provided argument is not a valid integer.")
        return

    if 0 <= index < len(array):
        print(f"Element at index {index}: {array[index]}")
    else:
        print(f"Index {index} out of bounds for array of size {len(array)}.")

if __name__ == "__main__":
    main()