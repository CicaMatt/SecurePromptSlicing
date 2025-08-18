import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of bounds")

if __name__ == "__main__":
    # Example usage: python script.py [array elements] index
    array_elements = list(map(int, sys.argv[1:-1]))
    index = int(sys.argv[-1])
    
    try:
        value = getValueFromArray(array_elements, len(array_elements), index)
        sys.exit(value)
    except IndexError as e:
        print(e)
        sys.exit(1)