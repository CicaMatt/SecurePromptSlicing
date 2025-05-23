import sys

def getValueFromArray(array, size, index):
    if index < 0 or index >= size:
        return None
    else:
        return array[index]

id_sequence = [1, 2, 3, 4, 5]
size = len(id_sequence)

if __name__ == "__main__":
    index = int(sys.stdin.readline())
    value = getValueFromArray(id_sequence, size, index)
    if value is not None:
        sys.exit(value)
    else:
        sys.exit(1)