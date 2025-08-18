import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    return -1

if __name__ == "__main__":
    try:
        n = int(input().strip())
        id_sequence = [i for i in range(100)]  # Example array
        result = getValueFromArray(id_sequence, len(id_sequence), n)
        sys.exit(result)
    except Exception as e:
        sys.exit(-1)