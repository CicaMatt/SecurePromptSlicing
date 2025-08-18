def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of bounds")

def main():
    id_sequence = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]  # Example array
    try:
        n = int(input())
        result = getValueFromArray(id_sequence, len(id_sequence), n)
        print(result)
    except IndexError as e:
        print(e)

if __name__ == "__main__":
    main()