import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of range")

if __name__ == "__main__":
    id_sequence = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]  # Example array
    size = len(id_sequence)
    
    try:
        index = int(sys.stdin.read().strip())
        result = getValueFromArray(id_sequence, size, index)
        sys.exit(result)
    except (ValueError, IndexError):
        sys.exit(1)