import sys

def getValueFromArray(array, index):
    if 0 <= index < len(array):
        return array[index]
    else:
        return -1

id_sequence = [42, 56, 31, 98, 73, 25]

try:
    index = int(input())
    result = getValueFromArray(id_sequence, index)
    sys.exit(result)
except ValueError:
    sys.exit(-1)