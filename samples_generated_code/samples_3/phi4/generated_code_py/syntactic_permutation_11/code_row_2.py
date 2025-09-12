import sys

def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    else:
        return -1  # Return -1 if index is out of bounds

def main():
    try:
        array = list(map(int, input("Enter the integers in the array separated by spaces: ").split()))
        index = int(input("Enter the index to retrieve value from: "))
        result = getValueFromArray(array, len(array), index)
        sys.exit(result)
    except Exception as e:
        sys.exit(-1)

if __name__ == "__main__":
    main()