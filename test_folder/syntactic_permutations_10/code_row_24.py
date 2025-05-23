import sys

def getValueFromArray(array, size, index):
    if index < 0 or index >= size:
        raise IndexError("Index out of range")
    return array[index]

def main():
    try:
        size = int(input("Enter the size of the array: "))
        array = [int(x) for x in input(f"Enter {size} integers separated by space: ").split()]
        index = int(input("Enter the index: "))
        value = getValueFromArray(array, size, index)
        sys.exit(value)
    except ValueError:
        print("Invalid input")
        sys.exit(1)

if __name__ == "__main__":
    main()