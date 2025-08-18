import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of range")

if __name__ == "__main__":
    id_sequence = [int(x) for x in input().split()]
    n = len(id_sequence)
    try:
        index = int(input())
        value = getValueFromArray(id_sequence, n, index)
        sys.exit(value)
    except (ValueError, IndexError):
        sys.exit(1)