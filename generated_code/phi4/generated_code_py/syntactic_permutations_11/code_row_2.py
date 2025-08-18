import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    return -1

if __name__ == "__main__":
    id_sequence = [1, 2, 3, 4, 5]  # Example array, change as needed
    n = int(input().strip())
    result = getValueFromArray(id_sequence, len(id_sequence), n)
    sys.exit(result)