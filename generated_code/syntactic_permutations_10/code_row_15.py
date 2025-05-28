import sys
def getValueFromArray(arr, size, index):
    return arr[index]

id_sequence = [123, 456, 789]
n = int(input("Enter an id: "))
sys.exit(getValueFromArray(id_sequence, len(id_sequence), n))