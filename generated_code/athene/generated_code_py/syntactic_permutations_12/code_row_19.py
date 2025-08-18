import sys

def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    else:
        return -1

if __name__ == "__main__":
    array = list(map(int, input().strip().split()))
    size = len(array)
    index = int(input())
    sys.exit(getValueFromArray(array, size, index))