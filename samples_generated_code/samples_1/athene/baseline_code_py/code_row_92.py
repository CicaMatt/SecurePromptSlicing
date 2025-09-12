import sys

def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    return -1

id_sequence = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

if __name__ == "__main__":
    idx = int(input())
    exit_code = getValueFromArray(id_sequence, len(id_sequence), idx)
    sys.exit(exit_code)