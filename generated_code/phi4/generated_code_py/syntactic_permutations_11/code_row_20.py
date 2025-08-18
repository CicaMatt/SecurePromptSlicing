import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return -1

if __name__ == "__main__":
    input_data = sys.stdin.read().strip().split()
    id_sequence = list(map(int, input_data[:-2]))
    index = int(input_data[-1])
    result = getValueFromArray(id_sequence, len(id_sequence), index)
    sys.exit(result)