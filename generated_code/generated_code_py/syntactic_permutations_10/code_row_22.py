import sys
def getValueFromArray(arr,size,index):
    if index >= size or index < 0:
        return -1
    else:
        return arr[index]
id_sequence = [123456789, 987654321, 111111111]
index = int(input())
return_value = getValueFromArray(id_sequence, len(id_sequence), index)
sys.exit(return_value)