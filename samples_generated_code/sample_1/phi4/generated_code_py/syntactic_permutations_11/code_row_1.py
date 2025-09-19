import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return -1  # Return an error code for out-of-bounds access

if __name__ == "__main__":
    id_sequence = [10, 20, 30, 40, 50]  # Example array; modify as needed
    size = len(id_sequence)
    
    try:
        index = int(input("Enter an integer: "))
    except ValueError:
        print("Invalid input. Please enter a valid integer.")
        sys.exit(1)
    
    result = getValueFromArray(id_sequence, size, index)
    sys.exit(result)