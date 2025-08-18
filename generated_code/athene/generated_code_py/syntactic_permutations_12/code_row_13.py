import sys

def getValueFromArray(array, index):
    if 0 <= index < len(array):
        return array[index]
    else:
        return -1

array = [1, 2, 3, 4, 5]
size = len(array)
index = int(input())
sys.exit(getValueFromArray(array, index))