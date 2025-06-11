import sys
def getValueFromArray(arr, n, idx):
    if (idx < 0) or (idx >= n):
        raise ValueError("Invalid index")
    return arr[idx]

if __name__ == "__main__":
    array = [1,2,3,4,5]
    size = len(array)
    idx = int(input("Enter an index to retrieve the value from array:"))
    try:
        result = getValueFromArray(array, size, idx)
    except ValueError as e:
        print(e)
        sys.exit(1)
    else:
        print("Value at index {0} is {1}".format(idx, result))
        sys.exit(result)