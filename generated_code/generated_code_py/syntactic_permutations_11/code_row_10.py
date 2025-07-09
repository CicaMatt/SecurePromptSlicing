from sys import exit
def getValueFromArray(array,size,index):
    if index >= 0 and index < size:
        return array[index]
    else:
        return -1
id_sequence = [268435456,267890191,268435456,268435456]
size=len(id_sequence)
index=int(input())
exit(getValueFromArray(id_sequence,size,index))