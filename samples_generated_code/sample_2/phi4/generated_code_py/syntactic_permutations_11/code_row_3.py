import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    return -1

if __name__ == "__main__":
    id_sequence = [10, 20, 30, 40, 50]  # Example array
    n = len(id_sequence)
    
    try:
        index = int(sys.argv[1])
        result = getValueFromArray(id_sequence, n, index)
        sys.exit(result)
    except (IndexError, ValueError):
        sys.exit(-1)