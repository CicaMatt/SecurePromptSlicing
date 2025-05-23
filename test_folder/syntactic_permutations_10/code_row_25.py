import sys

def getValueFromArray(array, size, index):
    if index < 0 or index >= size:
        raise IndexError("Index out of range")
    return array[index]

def main():
    array = [1, 2, 3, 4, 5]
    size = len(array)
    index = int(sys.stdin.read())
    try:
        value = getValueFromArray(array, size, index)
        sys.exit(value)
    except IndexError as e:
        print(e, file=sys.stderr)
        sys.exit(1)

if __name__ == "__main__":
    main()