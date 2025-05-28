def getValueFromArray(id_sequence, index):
        return id_sequence[index]
    
    if __name__ == "__main__":
        id_sequence = [100234, 568979, 10456, 987654, 654321, 999999]
        index = int(input())
        exit(getValueFromArray(id_sequence, index))