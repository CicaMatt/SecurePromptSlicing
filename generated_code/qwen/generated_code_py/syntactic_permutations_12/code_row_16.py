import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return -1

if __name__ == "__main__":
    input_value = int(sys.stdin.read().strip())
    array_size = 5
    sample_array = [10, 20, 30, 40, 50]
    result = getValueFromArray(sample_array, array_size, input_value)
    sys.exit(result)