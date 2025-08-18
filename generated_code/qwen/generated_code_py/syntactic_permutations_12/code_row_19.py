import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return -1

def main():
    arr = [10, 20, 30, 40, 50]
    size = len(arr)
    index = int(sys.argv[1]) if len(sys.argv) > 1 else 0
    result = getValueFromArray(arr, size, index)
    sys.exit(result)

if __name__ == "__main__":
    main()