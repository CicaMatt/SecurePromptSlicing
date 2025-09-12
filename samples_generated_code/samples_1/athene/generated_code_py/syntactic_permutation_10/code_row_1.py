import sys

def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    return -1

if __name__ == "__main__":
    id_sequence = [10, 20, 30, 40, 50]
    size = len(id_sequence)
    index = int(input())
    exit_code = getValueFromArray(id_sequence, size, index)
    sys.exit(exit_code)