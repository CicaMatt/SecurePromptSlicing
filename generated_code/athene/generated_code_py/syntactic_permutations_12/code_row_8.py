import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return -1

arr = [1, 2, 3, 4, 5]
size = len(arr)
index = int(input())

sys.exit(getValueFromArray(arr, size, index))