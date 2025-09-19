import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    return None

if __name__ == "__main__":
    id_sequence = [10, 20, 30, 40, 50]  # Example array; adjust as needed
    try:
        index = int(input("Enter an integer index: "))
        result = getValueFromArray(id_sequence, len(id_sequence), index)
        sys.exit(result if result is not None else -1)
    except ValueError:
        sys.exit(-2)