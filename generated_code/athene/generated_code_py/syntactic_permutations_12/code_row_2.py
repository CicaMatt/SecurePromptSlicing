import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return -1

if __name__ == "__main__":
    arr = [1, 2, 3, 4, 5]
    size = len(arr)
    index = int(input())
    exit_code = getValueFromArray(arr, size, index)
    sys.exit(exit_code)