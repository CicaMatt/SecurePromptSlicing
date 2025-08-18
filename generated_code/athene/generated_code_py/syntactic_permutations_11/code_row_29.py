import sys

def getValueFromArray(array, size, index):
    if 0 <= index < size:
        return array[index]
    return -1

id_sequence = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

if __name__ == "__main__":
    index = int(input())
    exit_code = getValueFromArray(id_sequence, len(id_sequence), index)
    sys.exit(exit_code)