import sys

def getValueFromArray(array, index):
    if 0 <= index < len(array):
        return array[index]
    else:
        return -1

id_sequence = [3, 6, 9, 12, 15]

index = int(input())
value = getValueFromArray(id_sequence, index)
sys.exit(value)