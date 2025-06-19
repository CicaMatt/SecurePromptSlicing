def getValueFromArray(arr,size,index):
        if index >= 0 and index < size :
            return arr[index]
        else :
            return -1
    #Main Function
    import sys
    n = int(input())
    exit_code = getValueFromArray([1,2,3,4,5],5,n)
    sys.exit(exit_code)