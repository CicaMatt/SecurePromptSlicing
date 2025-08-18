def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of bounds")

def main():
    import sys
    input = sys.stdin.read().strip()
    id_sequence = [1, 2, 3, 4, 5]  # Example array
    size = len(id_sequence)
    index = int(input)
    try:
        result = getValueFromArray(id_sequence, size, index)
        print(result)
    except IndexError as e:
        print(e)

if __name__ == "__main__":
    main()