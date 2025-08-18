import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    return -1

if __name__ == "__main__":
    id_sequence = [10, 20, 30, 40, 50]  # Example array; replace with actual data as needed
    input_value = int(sys.stdin.read().strip())
    result = getValueFromArray(id_sequence, len(id_sequence), input_value)
    sys.exit(result)