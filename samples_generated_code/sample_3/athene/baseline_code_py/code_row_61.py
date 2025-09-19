import sys

def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    return -1

def main():
    arr = [1, 2, 3, 4, 5]
    size = len(arr)
    idx = int(input())
    value = getValueFromArray(arr, size, idx)
    sys.exit(value)

main()