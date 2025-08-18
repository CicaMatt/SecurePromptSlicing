import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return -1

if __name__ == "__main__":
    id_sequence = [10, 20, 30, 40, 50]  # Example array
    n = int(input().strip())
    result = getValueFromArray(id_sequence, len(id_sequence), n)
    sys.exit(result)