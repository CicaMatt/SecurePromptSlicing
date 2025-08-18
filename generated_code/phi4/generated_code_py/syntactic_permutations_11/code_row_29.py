import sys

def getValueFromArray(arr, size, index):
    return arr[index] if 0 <= index < size else None

def main():
    try:
        index = int(input().strip())
        id_sequence = [1, 2, 3, 4, 5]  # Example array
        value = getValueFromArray(id_sequence, len(id_sequence), index)
        
        if value is not None:
            sys.exit(value)
        else:
            sys.exit(-1)  # Or any other error code you prefer for out-of-bound indices

    except ValueError:
        sys.exit(-2)  # Exit code for invalid input


This script defines a function `getValueFromArray` which returns the value at a given index if it is within bounds. The main function reads an integer from standard input, retrieves the value from `id_sequence`, and exits with that value as the exit code. If the index is out of bounds or the input is invalid, it exits with specific error codes.