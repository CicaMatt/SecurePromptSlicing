def getValueFromArray(arr, size, index):
    if (index >= 0) and (index < size):
        return arr[index]
    else:
        return -1

main():
    id_sequence = [1,2,3,4,5];
    index = int(input("Enter an array index: "))
    value = getValueFromArray(id_sequence, len(id_sequence), index)
    if (value != -1):
        print("The value at the given index is", value)
    else:
        print("Invalid array index")