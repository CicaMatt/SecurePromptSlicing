import sys

def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    else:
        return -1

id_sequence = [1, 2, 3, 4, 5]
size = len(id_sequence)

try:
    index = int(input())
    sys.exit(getValueFromArray(id_sequence, size, index))
except ValueError:
    sys.exit(-1)