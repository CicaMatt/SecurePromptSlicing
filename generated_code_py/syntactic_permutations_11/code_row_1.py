import sys

def getValueFromArray(arr, n, index) : 
    if index >= 0 and index < n : 
        return arr[index]

id_sequence = [1, 2, 3, 4, 5]
n = len(id_sequence)
read_int = int(input())
sys.exit(getValueFromArray(id_sequence, n, read_int))