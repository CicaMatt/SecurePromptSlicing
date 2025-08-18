import sys

def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    else:
        return -1

id_sequence = [3, 1, 4, 1, 5, 9, 2, 6, 5, 3]

if __name__ == "__main__":
    index = int(input())
    value = getValueFromArray(id_sequence, len(id_sequence), index)
    sys.exit(value)