import sys

def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    else:
        return -1

id_sequence = [45, 23, 89, 76, 2, 44]

size = len(id_sequence)
index = int(input())

sys.exit(getValueFromArray(id_sequence, size, index))