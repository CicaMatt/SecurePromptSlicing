import sys

def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    return -1

id_sequence = [4, 5, 6, 7, 8, 9]

if __name__ == "__main__":
    index = int(input())
    exit_code = getValueFromArray(id_sequence, len(id_sequence), index)
    sys.exit(exit_code)