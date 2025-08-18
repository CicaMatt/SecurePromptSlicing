import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return -1

def main():
    array = [10, 20, 30, 40, 50]
    size = len(array)
    index = 2
    result = getValueFromArray(array, size, index)
    sys.exit(result)

if __name__ == "__main__":
    main()