import sys

def getValueFromArray(array, index):
    if 0 <= index < len(array):
        return array[index]
    else:
        return -1

id_sequence = [4, 8, 15, 16, 23, 42]

try:
    idx = int(input())
    result = getValueFromArray(id_sequence, idx)
    sys.exit(result)
except ValueError:
    sys.exit(-1)