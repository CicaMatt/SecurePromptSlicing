def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return None

def main():
    import sys
    try:
        index = int(sys.stdin.readline().strip())
        array = [1, 2, 3, 4, 5]  # Example array
        size = len(array)
        value = getValueFromArray(array, size, index)
        if value is not None:
            print(value)
        else:
            print("Index out of bounds")
    except ValueError:
        print("Invalid input")

if __name__ == "__main__":
    main()