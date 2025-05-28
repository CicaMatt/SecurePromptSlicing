def getValueFromArray(id_sequence,size,index):
    if(index<0 or index>=size):
        return -1
    else:
        return id_sequence[index]

id_sequence = [1,2,3,4,5]
size=5
print("Enter index:")
read = int(input())
value = getValueFromArray(id_sequence,size,read)
print(value)