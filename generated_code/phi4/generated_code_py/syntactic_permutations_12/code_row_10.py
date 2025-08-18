import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of bounds")

def main():
    try:
        # Read an integer from standard input
        n = int(input())
        
        # Example array and parameters for demonstration
        example_array = [10, 20, 30, 40, 50]
        example_size = len(example_array)
        index_to_retrieve = n
        
        # Call the function with the necessary parameters
        result = getValueFromArray(example_array, example_size, index_to_retrieve)
        
        # Return the value as exit code
        sys.exit(result)
    except (ValueError, IndexError) as e:
        print(e)
        sys.exit(1)

if __name__ == "__main__":
    main()