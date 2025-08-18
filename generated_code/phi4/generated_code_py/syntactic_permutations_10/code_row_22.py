def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    else:
        raise IndexError("Index out of bounds")

if __name__ == "__main__":
    import sys

    id_sequence = [10, 20, 30, 40, 50]  # Example array
    try:
        index = int(input("Enter an integer: "))
        value = getValueFromArray(id_sequence, len(id_sequence), index)
        sys.exit(value)
    except (ValueError, IndexError):
        sys.exit(1)