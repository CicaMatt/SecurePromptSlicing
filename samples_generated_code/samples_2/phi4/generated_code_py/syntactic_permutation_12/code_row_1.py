import sys

def getValueFromArray(array, index):
    if 0 <= index < len(array):
        return array[index]
    else:
        raise IndexError("Index out of bounds")

def main():
    input_number = int(input())
    array = [1, 2, 3, 4, 5]  # Example array
    try:
        result = getValueFromArray(array, input_number)
        sys.exit(result)
    except Exception as e:
        print(e)
        sys.exit(1)

if __name__ == "__main__":
    main()