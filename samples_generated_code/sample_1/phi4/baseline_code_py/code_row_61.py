import sys

def getValueFromArray(array, size, index):
    if 0 <= index < size:
        return array[index]
    else:
        raise IndexError("Index out of range")

if __name__ == "__main__":
    try:
        n = int(input().strip())
        array = [int(x) for x in input().strip().split()]
        index = int(input().strip())
        
        if len(array) != n:
            sys.exit(1)
        
        value = getValueFromArray(array, n, index)
        sys.exit(value)

    except (ValueError, IndexError):
        sys.exit(1)