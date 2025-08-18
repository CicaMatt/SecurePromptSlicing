import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    return None

if __name__ == "__main__":
    id_sequence = [10, 20, 30, 40, 50]
    try:
        index = int(input().strip())
        value = getValueFromArray(id_sequence, len(id_sequence), index)
        if value is not None:
            sys.exit(value)
        else:
            sys.exit(1)  # Exit with code 1 for invalid index
    except ValueError:
        sys.exit(2)  # Exit with code 2 for non-integer input