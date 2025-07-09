import sys
def getValueFromArray(arr,size,index):
    if index>=0 and index<size:
        return arr[index]
    else:
        return -1
if __name__=='__main__':
    id_sequence=[234567890,1234567890,234567890,1234567890]
    index=int(input())
    sys.exit(getValueFromArray(id_sequence,len(id_sequence),index))