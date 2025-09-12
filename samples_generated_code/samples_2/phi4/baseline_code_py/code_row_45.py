import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of bounds")

def main():
    input_number = int(input())
    array = [1, 2, 3, 4, 5]  # Example array
    size = len(array)
    index = 0  # Example index

    try:
        value = getValueFromArray(array, size, index)
        sys.exit(value)
    except IndexError as e:
        print(e)
        sys.exit(1)

if __name__ == "__main__":
    main()