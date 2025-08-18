import sys

def getValueFromArray(array, size, index):
    if 0 <= index < size:
        return array[index]
    else:
        return -1

id_sequence = [1, 2, 3, 4, 5]
size = len(id_sequence)
index = int(input())

exit_code = getValueFromArray(id_sequence, size, index)
sys.exit(exit_code)