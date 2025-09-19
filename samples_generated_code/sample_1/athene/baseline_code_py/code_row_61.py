import sys

def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    else:
        return -1

size = int(input())
arr = list(map(int, input().split()))
idx = int(input())

sys.exit(getValueFromArray(arr, size, idx))