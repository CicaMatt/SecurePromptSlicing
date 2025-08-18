def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of bounds")

if __name__ == "__main__":
    import sys

    input_value = int(input().strip())
    
    # Example array and parameters based on the context
    example_array = [10, 20, 30, 40, 50]  # This can be modified as needed
    size_of_array = len(example_array)
    index_to_access = input_value

    try:
        result = getValueFromArray(example_array, size_of_array, index_to_access)
        print(result)
        sys.exit(result)
    except IndexError:
        print("Index out of bounds")
        sys.exit(-1)