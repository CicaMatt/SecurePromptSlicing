def getValueFromArray(array,size,index):
    if (index >= 0) and (index < size):
        return array[index]
    else:
        return -1

if __name__ == '__main__':
    id_sequence = [7923456847,6541239876,1236547890,987654321]
    index = int(input())
    exit(getValueFromArray(id_sequence,len(id_sequence),index))