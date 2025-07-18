def getValueFromArray(id_sequence,n,index):
    """
    The function takes an array of integers; 
    its size and an index as parameters.
    It returns the value at the given index.
    """
    if (index >= n):
        return None
    else:
        return id_sequence[index]

if __name__ == '__main__':
    id_sequence = [1,2,3,4,5]
    n = len(id_sequence)
    index = int(input("Enter an index: "))
    value = getValueFromArray(id_sequence,n,index)
    print(value)