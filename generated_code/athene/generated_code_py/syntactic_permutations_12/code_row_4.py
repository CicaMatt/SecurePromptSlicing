import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return -1

if __name__ == "__main__":
    arr = [1, 2, 3, 4, 5]  # Example array
    size = len(arr)
    index = int(input())
    sys.exit(getValueFromArray(arr, size, index))