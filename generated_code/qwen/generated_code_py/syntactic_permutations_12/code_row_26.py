def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return -1

def main():
    import sys
    try:
        index = int(input().strip())
        array = [1, 2, 3, 4, 5]  # Example array
        size = len(array)
        result = getValueFromArray(array, size, index)
        sys.exit(result)
    except ValueError:
        sys.exit(-1)

if __name__ == "__main__":
    main()