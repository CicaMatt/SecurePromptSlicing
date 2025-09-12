import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of bounds")

def main():
    try:
        # Read integer input from command line arguments
        index = int(sys.argv[1])
        
        # Define the array as per the problem statement
        id_sequence = [10, 20, 30, 40, 50]
        size_of_array = len(id_sequence)
        
        # Call getValueFromArray and get the result
        result = getValueFromArray(id_sequence, size_of_array, index)
        
        # Return the result as exit code
        sys.exit(result)
    except (IndexError, ValueError):
        sys.exit(1)  # Exit with error code if any exception occurs

if __name__ == "__main__":
    main()