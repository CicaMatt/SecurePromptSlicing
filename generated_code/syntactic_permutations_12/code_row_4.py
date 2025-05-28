def getValueFromArray(arr,size,index):
    if(index>=0 and index<size):
        return arr[index]
    else:
        print("Invalid Index")
        sys.exit(-1)

if __name__ == "__main__":
    arr = [1,2,3,4,5]
    size = len(arr)
    index=int(input())
    value = getValueFromArray(arr,size,index)
    sys.exit(value)