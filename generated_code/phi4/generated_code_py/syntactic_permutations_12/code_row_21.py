import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of range")

def main():
    try:
        n = int(input().strip())
        array = list(map(int, input().strip().split()))
        
        if len(array) != n:
            raise ValueError("Array length does not match the specified size")
        
        index = int(input().strip())

        value = getValueFromArray(array, n, index)
        sys.exit(value)

    except (ValueError, IndexError):
        print("An error occurred", file=sys.stderr)
        sys.exit(1)

if __name__ == "__main__":
    main()