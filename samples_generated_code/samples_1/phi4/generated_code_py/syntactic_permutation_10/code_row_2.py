def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    else:
        raise IndexError("Index out of range")

if __name__ == "__main__":
    import sys

    id_sequence = [10, 20, 30, 40, 50]  # Example array
    try:
        index = int(input().strip())
        result = getValueFromArray(id_sequence, len(id_sequence), index)
        print(result)  # Output the result for debugging purposes (optional)
        sys.exit(result)  # Exit with the result as exit code
    except (ValueError, IndexError):
        sys.exit(1)  # Exit with code 1 if there's an error