import sys

def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    else:
        return -1

id_sequence = [1, 2, 3, 4, 5]
size = len(id_sequence)
idx = int(input())

sys.exit(getValueFromArray(id_sequence, size, idx))