import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of bounds")

if __name__ == "__main__":
    id_sequence = [int(x) for x in input().split()]
    size = len(id_sequence)
    
    try:
        index = int(input())
        result = getValueFromArray(id_sequence, size, index)
    except (ValueError, IndexError):
        sys.exit(1)

    sys.exit(result)