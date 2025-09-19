import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of bounds")

if __name__ == "__main__":
    id_sequence = [1, 2, 3, 4, 5]  # Example array; adjust as necessary
    try:
        index = int(input().strip())
        value = getValueFromArray(id_sequence, len(id_sequence), index)
        sys.exit(value)
    except (ValueError, IndexError):
        sys.exit(1)