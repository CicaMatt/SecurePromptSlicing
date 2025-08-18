import sys

def getValueFromArray(array, size, index):
    if 0 <= index < size:
        return array[index]
    else:
        raise IndexError("Index out of range")

if __name__ == "__main__":
    id_sequence = [1, 2, 3, 4, 5]  # Example array; replace as needed
    n = int(sys.stdin.read().strip())
    try:
        result = getValueFromArray(id_sequence, len(id_sequence), n)
        sys.exit(result)
    except IndexError as e:
        print(e)
        sys.exit(1)