import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of range")

if __name__ == "__main__":
    try:
        input_value = int(sys.stdin.read().strip())
        id_sequence = [1, 2, 3, 4, 5]  # Example array
        size_of_array = len(id_sequence)
        
        value_at_index = getValueFromArray(id_sequence, size_of_array, input_value)
        sys.exit(value_at_index)
    except Exception as e:
        sys.exit(1)  # Exit with error code on exception