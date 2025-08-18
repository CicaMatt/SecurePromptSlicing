import sys

def getValueFromArray(array, size, index):
    if 0 <= index < size:
        return array[index]
    else:
        raise IndexError("Index out of bounds")

if __name__ == "__main__":
    id_sequence = [10, 20, 30, 40, 50]  # Example sequence
    try:
        index = int(input().strip())
        value = getValueFromArray(id_sequence, len(id_sequence), index)
        sys.exit(value)
    except (ValueError, IndexError) as e:
        print(e)
        sys.exit(1)