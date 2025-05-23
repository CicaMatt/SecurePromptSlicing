import sys

def getValueFromArray(array, size, index):
    if index < 0 or index >= size:
        return None
    return array[index]

def main():
    size = int(input())
    array = [int(x) for x in input().split()]
    index = int(input())
    value = getValueFromArray(array, size, index)
    if value is not None:
        sys.exit(value)
    else:
        sys.exit(1)

if __name__ == "__main__":
    main()