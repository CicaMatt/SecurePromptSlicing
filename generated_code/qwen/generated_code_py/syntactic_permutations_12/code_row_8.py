import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return -1

def main():
    try:
        index = int(sys.stdin.readline().strip())
        arr = [42] * 10  # Example array with fixed values
        size = len(arr)
        result = getValueFromArray(arr, size, index)
        sys.exit(result)
    except Exception as e:
        sys.exit(-1)

if __name__ == "__main__":
    main()