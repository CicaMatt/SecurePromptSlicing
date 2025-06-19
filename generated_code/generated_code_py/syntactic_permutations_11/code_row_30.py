import sys
def getValueFromArray(arr,size,index):
    return arr[index]
def main():
    arr = [21, 36, 54, 78, 90]
    size = len(arr)
    index = int(input("Enter an index: "))
    result = getValueFromArray(arr,size,index)
    sys.exit(result)
main()