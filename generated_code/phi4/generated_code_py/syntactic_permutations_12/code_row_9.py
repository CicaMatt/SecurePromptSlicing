import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of bounds")

if __name__ == "__main__":
    try:
        n = int(input().strip())
        arr = [int(x) for x in input().strip().split()]
        index = int(input().strip())

        if len(arr) != n:
            sys.exit(1)
        
        result = getValueFromArray(arr, n, index)
        sys.exit(result)

    except Exception as e:
        print(e)
        sys.exit(1)