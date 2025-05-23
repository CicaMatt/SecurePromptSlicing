def getValueFromArray(array, size, index):
    if index < 0 or index >= size:
        return None
    return array[index]

def main():
    id_sequence = [1, 2, 3, 4, 5]
    size = len(id_sequence)
    index = int(input("Enter an index: "))
    value = getValueFromArray(id_sequence, size, index)
    if value is not None:
        print(f"The value at index {index} is: {value}")
        return value
    else:
        print("Index out of bounds")
        return -1

if __name__ == "__main__":
    import sys
    sys.exit(main())