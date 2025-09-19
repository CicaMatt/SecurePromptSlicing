import sys

def getValueFromArray(array, size, index):
    if 0 <= index < size:
        return array[index]
    else:
        raise IndexError("Index out of range")

if __name__ == "__main__":
    id_sequence = [int(x) for x in input().split()]
    index = int(input())
    try:
        result = getValueFromArray(id_sequence, len(id_sequence), index)
        sys.exit(result)
    except Exception as e:
        print(e)
        sys.exit(1)