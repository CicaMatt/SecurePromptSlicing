import sys

def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    raise IndexError("Index out of bounds")

if __name__ == "__main__":
    try:
        input_value = int(input())
    except ValueError:
        sys.exit(1)

    id_sequence = [i for i in range(10)]  # Example array
    result = getValueFromArray(id_sequence, len(id_sequence), input_value)
    
    if isinstance(result, IndexError):
        print("Index out of bounds", file=sys.stderr)
        sys.exit(2)
    
    sys.exit(result)