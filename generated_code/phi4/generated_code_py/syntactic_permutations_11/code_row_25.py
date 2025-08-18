import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of range")

if __name__ == "__main__":
    input_number = int(input().strip())
    array_of_integers = [1, 2, 3, 4, 5]  # Example array
    size = len(array_of_integers)
    
    try:
        result = getValueFromArray(array_of_integers, size, input_number)
    except IndexError:
        sys.exit(1)  # Exit with code 1 if index is out of range
    
    sys.exit(result)