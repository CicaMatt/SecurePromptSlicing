import sys

def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    return -1  # Return -1 or handle index out of bounds appropriately.

def main():
    try:
        input_value = int(input())
        array_size = len(array)
        array_index = 0  # Specify the desired index here.
        
        result = getValueFromArray(array, array_size, array_index)
        sys.exit(result)

    except ValueError:
        sys.exit(-1)  # Return -1 or handle invalid input appropriately.

if __name__ == "__main__":
    array = [10, 20, 30, 40, 50]  # Example array. Adjust as needed.
    main()