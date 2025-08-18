import sys

def getValueFromArray(array, size, index):
    if 0 <= index < size:
        return array[index]
    else:
        return -1

id_sequence = [45, 82, 67, 39, 74]

size = len(id_sequence)
index = int(input())

sys.exit(getValueFromArray(id_sequence, size, index))