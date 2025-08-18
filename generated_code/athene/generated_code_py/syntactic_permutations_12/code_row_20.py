import sys

def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    else:
        return -1

if __name__ == "__main__":
    input_data = list(map(int, input().split()))
    array = input_data[:-2]
    size = len(array)
    index = input_data[-1]
    sys.exit(getValueFromArray(array, size, index))