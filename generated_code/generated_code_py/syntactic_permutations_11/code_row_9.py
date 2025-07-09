def getValueFromArray(id_sequence,size,index):
    if index >= size or index < 0:
        return None
    else:
        return id_sequence[index]

if __name__ == '__main__':
    import sys
    id_sequence = [1,2,3,4,5]
    size = len(id_sequence)
    index = int(input("Enter a value"))
    print(getValueFromArray(id_sequence,size,index))