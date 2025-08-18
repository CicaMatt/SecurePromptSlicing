import sys

def getValueFromArray(arr, index):
    return arr[index]

def main():
    try:
        index = int(input().strip())
        array_of_integers = [0, 1, 2, 3, 4, 5]  # Example array, can be modified as needed
        value = getValueFromArray(array_of_integers, index)
        sys.exit(value)
    except (IndexError, ValueError):
        sys.exit(1)

if __name__ == "__main__":
    main()