def getValueFromArray(arr,size,idx):
        if idx<0 or idx>=size:
            return 2147483647
        else:
            return arr[idx]
    
    def main():
        id_sequence = [1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144]
        size = len(id_sequence)
        idx = int(input())
        return getValueFromArray(id_sequence,size,idx)
    
    main()