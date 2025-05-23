def getValueFromArray(array, size, index):
    if index < 0 or index >= size:
        raise IndexError("Index out of range")
    return array[index]

def main():
    id_sequence = [1, 2, 3, 4, 5]
    size = len(id_sequence)
    index = int(input())
    return getValueFromArray(id_sequence, size, index)

print(main())