import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return -1  # Return -1 for invalid index

def main():
    try:
        index = int(input().strip())
        array_size = 5
        sample_array = [10, 20, 30, 40, 50]  # Example array
        result = getValueFromArray(sample_array, array_size, index)
        sys.exit(result)
    except ValueError:
        sys.exit(-1)  # Exit with -1 if input is not an integer

if __name__ == "__main__":
    main()