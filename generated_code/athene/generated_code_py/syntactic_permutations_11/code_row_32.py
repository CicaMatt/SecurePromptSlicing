import sys

def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    else:
        return -1

id_sequence = [10, 20, 30, 40, 50]

if __name__ == "__main__":
    index = int(input().strip())
    exit_code = getValueFromArray(id_sequence, len(id_sequence), index)
    sys.exit(exit_code)