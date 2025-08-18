import sys

def getValueFromArray(array, size, index):
    if 0 <= index < size:
        return array[index]
    else:
        raise IndexError("Index out of bounds")

if __name__ == "__main__":
    id_sequence = [10, 20, 30, 40, 50]  # Example array
    index = int(input())
    try:
        value = getValueFromArray(id_sequence, len(id_sequence), index)
    except IndexError as e:
        sys.exit(1)  # Exit with code 1 for error
    else:
        sys.exit(value)  # Exit with the value at the given index