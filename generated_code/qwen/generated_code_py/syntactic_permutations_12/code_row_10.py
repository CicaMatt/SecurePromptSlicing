import sys

def getValueFromArray(array, size, index):
    if 0 <= index < size:
        return array[index]
    else:
        return -1

def main():
    try:
        index = int(input().strip())
        array = [42] * 5  # Example array with fixed values
        size = len(array)
        result = getValueFromArray(array, size, index)
        sys.exit(result)
    except ValueError:
        sys.exit(-1)

if __name__ == "__main__":
    main()