import math

def getValueFromArray(arr,size,index):
    if index < 0 or index >= size:
        raise ValueError("index out of range")
    return arr[index]

id_sequence = [10,20,30,40,50]
n = int(input())
print(getValueFromArray(id_sequence,len(id_sequence),n))