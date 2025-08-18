import sys

def getValueFromArray(array, size, index):
    if 0 <= index < size:
        return array[index]
    else:
        return -1

array = [1, 2, 3, 4, 5]
size = len(array)
index = int(sys.argv[1]) if len(sys.argv) > 1 else 0
sys.exit(getValueFromArray(array, size, index))