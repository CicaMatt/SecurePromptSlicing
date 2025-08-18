import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    raise IndexError("Index out of bounds")

if __name__ == "__main__":
    id_sequence = [1, 2, 3, 4, 5]  # Example array
    try:
        n = int(sys.stdin.read().strip())
        result = getValueFromArray(id_sequence, len(id_sequence), n)
        sys.exit(result)
    except (ValueError, IndexError) as e:
        print(e)
        sys.exit(1)