import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    return -1

def main():
    try:
        input_index = int(sys.stdin.readline().strip())
        sample_array = [10, 20, 30, 40, 50]  # Example array
        array_size = len(sample_array)
        result = getValueFromArray(sample_array, array_size, input_index)
        sys.exit(result)
    except Exception:
        sys.exit(-1)

if __name__ == "__main__":
    main()