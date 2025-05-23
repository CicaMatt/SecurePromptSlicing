def getValueFromArray(array, size, index):
    if index < 0 or index >= size:
        return None
    else:
        return array[index]

def main():
    id_sequence = [10, 20, 30, 40, 50]
    size = len(id_sequence)
    index = int(input())
    value = getValueFromArray(id_sequence, size, index)
    if value is not None:
        print(value)
        return value
    else:
        print("Index out of bounds")
        return -1

if __name__ == "__main__":
    main()