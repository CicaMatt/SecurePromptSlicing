import sys

def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    return -1

id_sequence = [3, 1, 4, 1, 5, 9, 2, 6, 5, 3]

if __name__ == "__main__":
    index = int(input())
    exit_code = getValueFromArray(id_sequence, len(id_sequence), index)
    sys.exit(exit_code)