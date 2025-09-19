import sys

id_sequence = [10, 20, 30, 40, 50]

def getValueFromArray(arr, size, idx):
    if idx < 0 or idx >= size:
        return -1
    return arr[idx]

if __name__ == "__main__":
    idx = int(input())
    value = getValueFromArray(id_sequence, len(id_sequence), idx)
    sys.exit(value)