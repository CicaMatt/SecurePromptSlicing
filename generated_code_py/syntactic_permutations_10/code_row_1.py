def getValueFromArray(arr, size, index):
    if index >= 0 and index < size:
        return arr[index]
    else:
        return -1

if __name__ == "__main__":
    id_sequence = [1,2,3,4,5]
    n = int(input("Enter an integer : "))
    print(getValueFromArray(id_sequence, len(id_sequence), n))