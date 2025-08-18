import sys

def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    else:
        return -1

id_sequence = [34, 78, 52, 91, 16]

if __name__ == "__main__":
    index = int(input())
    result = getValueFromArray(id_sequence, len(id_sequence), index)
    sys.exit(result)