import sys

def getValueFromArray(array, size, index):
    if 0 <= index < size:
        return array[index]
    return -1

if __name__ == "__main__":
    array = [1, 2, 3, 4, 5]
    size = len(array)
    index = int(input())
    sys.exit(getValueFromArray(array, size, index))