import sys

def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    else:
        return -1

id_sequence = [4, 5, 6, 7, 8, 9]

size = len(id_sequence)
idx = int(input())

exit_code = getValueFromArray(id_sequence, size, idx)

sys.exit(exit_code)