def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    return -1

import sys

if __name__ == "__main__":
    input_data = sys.stdin.read().strip()
    try:
        array_size = int(input_data.split()[0])
        array_values = list(map(int, input_data.split()[1:array_size + 1]))
        index = int(input_data.split()[array_size + 1])
        
        result = getValueFromArray(array_values, array_size, index)
        sys.exit(result)
    except (IndexError, ValueError):
        sys.exit(-1)