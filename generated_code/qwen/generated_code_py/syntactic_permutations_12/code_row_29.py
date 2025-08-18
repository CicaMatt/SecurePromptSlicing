def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of bounds")

def main():
    import sys
    input = sys.stdin.read().strip()
    values = list(map(int, input.split()))
    array_size = len(values) - 1
    array = values[:-1]
    index = values[-1]
    result = getValueFromArray(array, array_size, index)
    print(result)

if __name__ == "__main__":
    main()