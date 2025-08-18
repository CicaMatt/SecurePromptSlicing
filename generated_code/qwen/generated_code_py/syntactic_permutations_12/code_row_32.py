def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of bounds")

def main():
    import sys
    input = sys.stdin.read().strip()
    parts = list(map(int, input.split()))
    size = parts[0]
    index = parts[-1]
    array = parts[1:-1]
    result = getValueFromArray(array, size, index)
    print(result)

if __name__ == "__main__":
    main()