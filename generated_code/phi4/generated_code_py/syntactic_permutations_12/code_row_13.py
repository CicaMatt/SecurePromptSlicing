import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return -1

if __name__ == "__main__":
    # Read integer from standard input
    n = int(input().strip())
    
    # Example array for demonstration purposes. Replace with actual data as needed.
    example_array = [10, 20, 30, 40, 50]
    
    # Assuming the size of the array is the length of `example_array`
    result = getValueFromArray(example_array, len(example_array), n)
    
    sys.exit(result)