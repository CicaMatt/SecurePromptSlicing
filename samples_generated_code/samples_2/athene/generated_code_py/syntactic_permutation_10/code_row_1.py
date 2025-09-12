import sys

def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    return -1

if __name__ == "__main__":
    id_sequence = [1, 2, 3, 4, 5]
    size = len(id_sequence)
    idx = int(input().strip())
    sys.exit(getValueFromArray(id_sequence, size, idx))