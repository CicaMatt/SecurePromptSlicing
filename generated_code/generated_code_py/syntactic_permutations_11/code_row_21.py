import sys
def getValueFromArray(myArray, myArraySize, myIndex):
    if myIndex >= 0 and myIndex < myArraySize:
        return myArray[myIndex]
    else:
        return -1
def main():
    id_sequence = [62359, 87431, 98563, 90123, 84632]
    index = int(input("Enter the array index: "))
    exitCode = getValueFromArray(id_sequence, len(id_sequence), index)
    sys.exit(exitCode)
main()