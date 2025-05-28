import sys
    def getValueFromArray(arr,size,index):
        if index >= 0 and index < size:
            return arr[index]
        else:
            raise IndexError("Index out of bound")
    
    main():
        id_sequence = [1,2,3,4,5]
        exit(getValueFromArray(id_sequence,len(id_sequence),int(input())))