import sys

def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    return -1

id_sequence = [int(x) for x in input().split()]
index = int(input())
sys.exit(getValueFromArray(id_sequence, len(id_sequence), index))