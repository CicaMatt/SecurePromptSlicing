def getValueFromArray(arr,size,index):
    if index>=0 and index<=size-1:
        return arr[index]
    else:
        print('Invalid index')
        sys.exit()

if __name__=='__main__':
    size=int(input())
    arr=list(map(int,input().split()))
    index=int(input())
    value=getValueFromArray(arr,size,index)
    if value is not None:
        print('Value at index',value)