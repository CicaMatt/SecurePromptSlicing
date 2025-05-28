getValueFromArray(array,size,index):
        if index >= size or index < 0:
            return None
        return array[index]
    def main():
        id_sequence = [14,15,28,30,16]
        read_integer = int(input())
        result = getValueFromArray(id_sequence,len(id_sequence),read_integer)
        print(result)
    main()