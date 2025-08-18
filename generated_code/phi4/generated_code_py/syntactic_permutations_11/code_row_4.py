import sys

def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    return -1

if __name__ == "__main__":
    input_value = int(input().strip())
    id_sequence = [1, 2, 3, 4, 5]  # Example array
    result = getValueFromArray(id_sequence, len(id_sequence), input_value)
    sys.exit(result)