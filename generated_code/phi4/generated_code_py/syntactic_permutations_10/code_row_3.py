import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of bounds")

if __name__ == "__main__":
    id_sequence = [1, 2, 3, 4, 5]  # Example array
    n = int(sys.stdin.read().strip())
    try:
        result = getValueFromArray(id_sequence, len(id_sequence), n)
    except IndexError as e:
        sys.exit(1)  # Exit with code 1 if index is out of bounds
    
    sys.exit(result)