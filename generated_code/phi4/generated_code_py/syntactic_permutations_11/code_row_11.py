import sys

def getValueFromArray(array, size, index):
    if 0 <= index < size:
        return array[index]
    return None

if __name__ == "__main__":
    id_sequence = [10, 20, 30, 40, 50]  # Example array; replace with actual values as needed
    try:
        index = int(input())
        result = getValueFromArray(id_sequence, len(id_sequence), index)
        if result is not None:
            sys.exit(result)
        else:
            sys.exit(1)  # Exit code for an invalid index
    except ValueError:
        sys.exit(1)  # Exit code for non-integer input