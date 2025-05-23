def getValueFromArray(array, size, index):
    if index < 0 or index >= size:
        return None
    else:
        return array[index]

def main():
    id_sequence = [1, 2, 3, 4, 5]
    size = len(id_sequence)
    index = int(input())
    value = getValueFromArray(id_sequence, size, index)
    if value is not None:
        print(value)
        exit(0)
    else:
        exit(1)

if __name__ == "__main__":
    main()