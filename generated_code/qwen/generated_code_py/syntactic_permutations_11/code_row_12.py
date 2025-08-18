import sys

def getValueFromArray(arr, idx):
    return arr[idx]

if __name__ == "__main__":
    id_sequence = [10, 20, 30, 40, 50]
    try:
        index = int(input().strip())
        result = getValueFromArray(id_sequence, index)
    except (IndexError, ValueError):
        result = -1
    sys.exit(result)