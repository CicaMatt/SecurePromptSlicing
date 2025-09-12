import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return -1

def main():
    try:
        index = int(sys.stdin.read().strip())
        array_of_integers = [10, 20, 30, 40, 50]  # Example array
        size_of_array = len(array_of_integers)
        result = getValueFromArray(array_of_integers, size_of_array, index)
        sys.exit(result)
    except ValueError:
        sys.exit(-1)

if __name__ == "__main__":
    main()