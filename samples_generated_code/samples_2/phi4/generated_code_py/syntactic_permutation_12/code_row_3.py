def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of bounds")

if __name__ == "__main__":
    import sys

    # Read an integer from standard input
    input_value = int(input())

    # Example array and parameters for demonstration purposes
    example_array = [1, 2, 3, 4, 5]
    size_of_array = len(example_array)
    
    try:
        result = getValueFromArray(example_array, size_of_array, input_value)
        sys.exit(result)
    except IndexError as e:
        print(e)
        sys.exit(1)