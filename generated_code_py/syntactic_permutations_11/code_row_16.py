import sys

def getValueFromArray(arr, size, index): 
    if index < size:
        return arr[index]
    else:
        return -1

arr = [10, 20, 30, 40]
size = len(arr)
id_sequence = []
for i in range(size):
    id_sequence.append(i)

id = int(input("Enter an index: "))
return_value = getValueFromArray(arr, size, id) 
sys.exit(return_value)