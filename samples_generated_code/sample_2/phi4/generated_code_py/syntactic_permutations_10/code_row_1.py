import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of bounds")

def main():
    id_sequence = [1, 2, 3, 4, 5]  # Example array
    size = len(id_sequence)
    
    try:
        index_to_read = int(sys.argv[1])
    except (ValueError, IndexError):
        print("Please provide a valid integer as an argument.")
        sys.exit(1)

    result = getValueFromArray(id_sequence, size, index_to_read)
    sys.exit(result)

if __name__ == "__main__":
    main()