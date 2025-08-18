import sys

def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    else:
        return -1

id_sequence = [10, 20, 30, 40, 50]

input_idx = int(input())
sys.exit(getValueFromArray(id_sequence, len(id_sequence), input_idx))