import sys

def getValueFromArray(array, size, index):
    if 0 <= index < size:
        return array[index]
    else:
        return -1

id_sequence = [10, 20, 30, 40, 50]
size = len(id_sequence)
index = int(input())

sys.exit(getValueFromArray(id_sequence, size, index))