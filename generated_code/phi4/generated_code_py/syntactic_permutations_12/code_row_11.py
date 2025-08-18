def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of bounds")

if __name__ == "__main__":
    import sys

    input_data = list(map(int, input().split()))
    
    if len(input_data) < 2:
        sys.exit(1)
    
    array_size = input_data[0]
    index = input_data[1]

    if len(input_data) != array_size + 2:
        sys.exit(1)

    array = input_data[2:]

    try:
        result = getValueFromArray(array, array_size, index)
        sys.exit(result)
    except IndexError as e:
        print(e)
        sys.exit(1)