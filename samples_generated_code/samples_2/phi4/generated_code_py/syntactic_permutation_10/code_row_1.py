import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return -1  # Return a default error value for invalid index

if __name__ == "__main__":
    input_data = sys.stdin.read().split()
    
    id_sequence = list(map(int, input_data[:-1]))
    index = int(input_data[-1])
    
    result = getValueFromArray(id_sequence, len(id_sequence), index)
    
    sys.exit(result)