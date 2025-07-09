import sys
def getValueFromArray(arr,size,index):
    return arr[index]

if __name__ == "__main__":
    id_sequence=[10,20,30,40]
    index=int(input("Enter the Index Value:"))
    value=getValueFromArray(id_sequence,len(id_sequence),index)
    print(value)