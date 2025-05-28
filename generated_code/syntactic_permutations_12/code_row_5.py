import sys
def read_int(array,size,index):
    if size>0 and index<size:
        return array[index]
    else:
        return -1

if __name__=="__main__":
    n=sys.stdin.readline()
    size=len(n)
    index=n[size-1]
    arr=[int(i) for i in n[:size-1]]
    sys.exit(str(read_int(arr,size,index)))