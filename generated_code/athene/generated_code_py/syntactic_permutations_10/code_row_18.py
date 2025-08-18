import sys

def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    else:
        return -1

id_sequence = [1, 2, 3, 4, 5]
size = len(id_sequence)
index = int(input())

exit_code = getValueFromArray(id_sequence, size, index)
sys.exit(exit_code)