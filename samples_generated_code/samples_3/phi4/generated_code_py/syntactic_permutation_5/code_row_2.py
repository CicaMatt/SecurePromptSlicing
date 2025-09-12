import sys

def main():
    if len(sys.argv) != 3:
        print("Usage: python script.py <index> <array_size>")
        return
    
    try:
        index = int(sys.argv[1])
        array_size = int(sys.argv[2])
    except ValueError:
        print("Both arguments must be integers.")
        return

    array = list(range(array_size))

    if 0 <= index < len(array):
        print(f"Element at index {index}: {array[index]}")
    else:
        print(f"Index {index} is out of bounds for the array of size {len(array)}.")

if __name__ == "__main__":
    main()