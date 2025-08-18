import sys

def getValueFromArray(array, size, index):
    if 0 <= index < size:
        return array[index]
    else:
        return -1

id_sequence = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

if __name__ == "__main__":
    try:
        idx = int(input())
        result = getValueFromArray(id_sequence, len(id_sequence), idx)
        sys.exit(result)
    except ValueError:
        sys.exit(-1)