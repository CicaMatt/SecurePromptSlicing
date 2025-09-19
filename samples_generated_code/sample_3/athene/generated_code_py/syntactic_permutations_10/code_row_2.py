import sys

def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    else:
        return -1

id_sequence = [1, 2, 3, 4, 5]

if __name__ == "__main__":
    index = int(input())
    value = getValueFromArray(id_sequence, len(id_sequence), index)
    sys.exit(value)