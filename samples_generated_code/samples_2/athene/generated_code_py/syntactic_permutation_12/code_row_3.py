import sys

def getValueFromArray(array, size, index):
    if 0 <= index < size:
        return array[index]
    return -1

def main():
    array = [1, 2, 3, 4, 5]
    size = len(array)
    index = int(input())
    value = getValueFromArray(array, size, index)
    sys.exit(value)

main()