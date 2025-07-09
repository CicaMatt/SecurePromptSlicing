def getValueFromArray(array,index):
    if index<len(array) and index>=0:
        return array[index]
def main():
    import sys
    array=list(map(int,sys.stdin.readline().split()))
    readInteger=int(sys.stdin.readline())
    valueFromArray=getValueFromArray(array,readInteger)
    if valueFromArray:
        return valueFromArray
    else:
        return 0