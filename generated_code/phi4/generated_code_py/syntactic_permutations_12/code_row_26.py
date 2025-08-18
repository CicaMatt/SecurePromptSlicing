def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return -1

if __name__ == "__main__":
    import sys
    
    input_value = int(input().strip())
    
    # Example array and parameters for demonstration purposes
    arr = [10, 20, 30, 40, 50]  # Replace with actual values as needed
    size = len(arr)
    
    result = getValueFromArray(arr, size, input_value)
    
    sys.exit(result)