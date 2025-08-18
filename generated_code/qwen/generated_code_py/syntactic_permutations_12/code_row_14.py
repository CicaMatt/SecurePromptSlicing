import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return -1

def main():
    try:
        index = int(input())
        array_of_integers = [1, 2, 3, 4, 5]  # Example array
        size_of_array = len(array_of_integers)
        result = getValueFromArray(array_of_integers, size_of_array, index)
        sys.exit(result)
    except ValueError:
        sys.exit(-1)

if __name__ == "__main__":
    main()