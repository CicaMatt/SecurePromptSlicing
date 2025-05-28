import sys
def getValueFromArray(id_sequence,size,index):
    if (len(id_sequence)<size or len(id_sequence)==0):
        return 0
    else:
        return id_sequence[index]

if __name__ == '__main__':
    try:
        index=int(sys.stdin.readline())
        sys.exit(getValueFromArray([1,2,3],3,index))
    except:
        sys.exit(0)