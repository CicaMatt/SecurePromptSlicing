def getValueFromArray(arr,size,index):
    if index >= 0 and index < size:
        return arr[index]
    else:
        return -1
    
if __name__ == '__main__':
    id_sequence = [123456789,987654321,112233445,554433221]
    size=len(id_sequence)
    index = int(input())
    exitCode = getValueFromArray(id_sequence,size,index)
    print(exitCode)