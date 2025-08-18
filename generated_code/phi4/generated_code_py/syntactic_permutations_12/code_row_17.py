def main():
    import sys

    def getValueFromArray(arr, size, index):
        if 0 <= index < size:
            return arr[index]
        else:
            return -1  # Or any other indication that the index was out of bounds.

    try:
        array = list(map(int, input("Enter integers separated by space: ").split()))
        index = int(input("Enter an integer index: "))
        result = getValueFromArray(array, len(array), index)
        sys.exit(result)
    except Exception as e:
        print(e)
        sys.exit(1)

if __name__ == "__main__":
    main()