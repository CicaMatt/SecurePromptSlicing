import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return -1

if __name__ == "__main__":
    size = int(input())
    arr = list(map(int, input().split()))
    index = int(input())
    sys.exit(getValueFromArray(arr, size, index))