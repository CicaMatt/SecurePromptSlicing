import sys

def getValueFromArray(array, index):
    try:
        return array[index]
    except IndexError:
        return -1

if __name__ == "__main__":
    arr = [1, 2, 3, 4, 5]
    idx = int(input())
    sys.exit(getValueFromArray(arr, idx))