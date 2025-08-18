import sys

def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    else:
        return -1

if __name__ == "__main__":
    arr = list(map(int, input().strip().split()))
    size = len(arr)
    idx = int(input())
    sys.exit(getValueFromArray(arr, size, idx))