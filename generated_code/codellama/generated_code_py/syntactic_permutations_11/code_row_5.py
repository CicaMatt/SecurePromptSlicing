import sys
def getValueFromArray(arr,size,index):
    if index>=0 and index<size:
        return arr[index]
    else:
        return -1
def main():
    id_sequence=[1,2,3,4,5]
    n=int(input("enter a number"))
    return getValueFromArray(id_sequence,len(id_sequence),n)
if __name__ == '__main__':
   sys.exit(main())