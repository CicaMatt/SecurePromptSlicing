import sys

def getValueFromArray(array, size, index):
    if index < 0 or index >= size:
        return None
    else:
        return array[index]

id_sequence = [10, 20, 30, 40, 50]
size = len(id_sequence)

index = int(sys.stdin.read())
print(getValueFromArray(id_sequence, size, index))
sys.exit(getValueFromArray(id_sequence, size, index) if getValueFromArray(id_sequence, size, index) is not None else 0)