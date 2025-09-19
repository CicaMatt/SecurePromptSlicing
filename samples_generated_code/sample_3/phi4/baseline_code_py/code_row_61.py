import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of bounds")

def main():
    try:
        n = int(input())
        array = list(map(int, input().split()))
        
        if len(array) != n:
            sys.exit(1)
        
        index = int(input())
        result = getValueFromArray(array, n, index)
        sys.exit(result)

    except (ValueError, IndexError):
        sys.exit(1)

if __name__ == "__main__":
    main()