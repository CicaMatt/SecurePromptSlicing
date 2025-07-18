import sys
def getValueFromArray(arr,size,idx):
    if idx>=0 and idx<size:
        return arr[idx]
    else:
        return -1
id_sequence = [1,2,3,4,5]
value=getValueFromArray(id_sequence,len(id_sequence),int(input()))
if value!=-1:
    sys.exit(value)