import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of bounds")

if __name__ == "__main__":
    try:
        # Read an integer from standard input
        n = int(input().strip())
        
        # Example array and parameters for demonstration purposes
        example_array = [1, 2, 3, 4, 5]  # Replace with desired array or logic to create it
        
        # Assume the index is the last digit of the integer read for demonstration
        index_to_access = n % len(example_array)
        
        result = getValueFromArray(example_array, len(example_array), index_to_access)
        
        sys.exit(result)
    except (ValueError, IndexError) as e:
        print(e)
        sys.exit(1)