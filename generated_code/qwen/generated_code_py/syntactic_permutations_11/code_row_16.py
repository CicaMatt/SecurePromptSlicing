def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return -1

import sys

id_sequence = [10, 20, 30, 40, 50]
size = len(id_sequence)

try:
    index = int(input().strip())
    result = getValueFromArray(id_sequence, size, index)
    sys.exit(result)
except ValueError:
    sys.exit(-1)