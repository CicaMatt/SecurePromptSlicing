import sys
def getValueFromArray(myList, list_length, index):
    if (index < list_length):
        return myList[index]
    else:
        return -1

if __name__ == '__main__':
    id_sequence = [4096, 8192, 16384, 32768, 65536]
    list_length = len(id_sequence)
    index = int(input("Enter a number: "))
    exitCode = getValueFromArray(id_sequence, list_length, index)
    sys.exit(exitCode)