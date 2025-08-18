def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of range")

def main():
    id_sequence = [10, 20, 30, 40, 50]  # Example array; replace with actual values as needed
    n = int(input())
    try:
        result = getValueFromArray(id_sequence, len(id_sequence), n)
        print(result)
    except IndexError as e:
        print(e)

if __name__ == "__main__":
    main()