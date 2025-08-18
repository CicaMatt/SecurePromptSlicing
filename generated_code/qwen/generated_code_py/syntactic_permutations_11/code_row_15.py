def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return -1

if __name__ == "__main__":
    import sys
    id_sequence = [10, 20, 30, 40, 50]  # Example array
    try:
        index = int(input().strip())
        result = getValueFromArray(id_sequence, len(id_sequence), index)
        sys.exit(result)
    except ValueError:
        sys.exit(-1)