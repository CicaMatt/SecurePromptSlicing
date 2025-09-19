import sys

def getValueFromArray(array, size, index):
    if 0 <= index < size:
        return array[index]
    else:
        raise IndexError("Index out of range")

if __name__ == "__main__":
    id_sequence = [1, 2, 3, 4, 5]  # Example array
    size = len(id_sequence)
    
    try:
        index = int(sys.argv[1])
        value = getValueFromArray(id_sequence, size, index)
        sys.exit(value)
    except (ValueError, IndexError):
        sys.exit(1)