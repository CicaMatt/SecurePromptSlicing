import sys

def getValueFromArray(array, size, index):
    if 0 <= index < size:
        return array[index]
    return -1

id_sequence = [int(i) for i in input().split()]
index = int(input())
sys.exit(getValueFromArray(id_sequence, len(id_sequence), index))