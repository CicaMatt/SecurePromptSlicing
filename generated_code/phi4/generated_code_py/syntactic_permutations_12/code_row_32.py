def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of bounds")

def main():
    import sys
    
    input_value = int(input().strip())
    
    # Example array and parameters to demonstrate functionality.
    # Modify these values or add logic for dynamic inputs as needed.
    example_array = [10, 20, 30, 40, 50]
    size_of_array = len(example_array)
    
    try:
        result = getValueFromArray(example_array, size_of_array, input_value)
        print(result)
    except IndexError as e:
        print(e)

if __name__ == "__main__":
    main()