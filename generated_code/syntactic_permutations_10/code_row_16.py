import sys
def getValueFromArray(arr, size, idx):
    if (idx >= 0 and idx < size):
        return arr[idx]
    else:
        return -1
id_sequence = [1, 2, 3, 4, 5]
size = len(id_sequence)
index = int(input("Enter index: "))
sys.exit(getValueFromArray(id_sequence, size, index))