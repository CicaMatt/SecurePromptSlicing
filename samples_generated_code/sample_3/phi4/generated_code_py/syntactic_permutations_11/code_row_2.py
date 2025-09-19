import sys

def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    else:
        raise IndexError("Index out of bounds")

if __name__ == "__main__":
    try:
        # Read an integer from standard input (index)
        index = int(input().strip())
        
        # Define the id_sequence array
        id_sequence = [10, 20, 30, 40, 50]
        size = len(id_sequence)
        
        # Call getValueFromArray and use its return value as exit code
        result = getValueFromArray(id_sequence, size, index)
        sys.exit(result)
    except Exception as e:
        print(e)
        sys.exit(1)