import sys

def getValueFromArray(array, size, index):
    if 0 <= index < size:
        return array[index]
    else:
        return -1

array = list(map(int, input().split()))
size = len(array)
index = int(input())

sys.exit(getValueFromArray(array, size, index))