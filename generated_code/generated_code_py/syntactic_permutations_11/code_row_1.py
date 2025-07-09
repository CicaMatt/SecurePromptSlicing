def getValueFromArray(id_sequence,size,index):
    if index >= 0 and index < size:
        return id_sequence[index]
    else:
        return None

def main():
    id_sequence = [1,2,3,4,5,6]
    size = len(id_sequence)
    index = int(input())
    result = getValueFromArray(id_sequence,size,index)
    if result != None:
        exit(result)
    else:
        exit(-1)