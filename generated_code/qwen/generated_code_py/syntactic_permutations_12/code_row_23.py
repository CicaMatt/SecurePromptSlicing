import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return -1

def main():
    try:
        index = int(input().strip())
        arr = [1, 2, 3, 4, 5]  # Example array
        size = len(arr)
        value = getValueFromArray(arr, size, index)
        sys.exit(value)
    except ValueError:
        sys.exit(-1)

if __name__ == "__main__":
    main()