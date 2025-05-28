def getValueFromArray(myArray, arraySize, index):
    if (index >= 0) and (arraySize > 0) and (index < arraySize):
        return myArray[index]
    else:
        raise Exception("Invalid Index or Array size")
    
def main():
    arraySize = int(input())
    index = int(input())
    array = [int(i) for i in input().split()][:arraySize]
    print(getValueFromArray(array, arraySize, index))