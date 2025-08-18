def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of bounds")

def main():
    import sys

    input_value = int(sys.stdin.readline().strip())
    
    # Example array and index for demonstration purposes
    example_array = [1, 2, 3, 4, 5]
    size_of_array = len(example_array)
    index_to_access = input_value
    
    try:
        value = getValueFromArray(example_array, size_of_array, index_to_access)
        print(value)
    except IndexError as e:
        print(e)

if __name__ == "__main__":
    main()