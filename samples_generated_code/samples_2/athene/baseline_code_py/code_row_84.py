import sys

def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    return -1

id_sequence = [10, 20, 30, 40, 50]

if __name__ == "__main__":
    idx = int(input())
    exit_code = getValueFromArray(id_sequence, len(id_sequence), idx)
    sys.exit(exit_code)