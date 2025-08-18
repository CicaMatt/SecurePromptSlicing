import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of bounds")

if __name__ == "__main__":
    try:
        n = int(input().strip())
        array_elements = [int(input().strip()) for _ in range(n)]
        idx = int(input().strip())
        
        result = getValueFromArray(array_elements, len(array_elements), idx)
        sys.exit(result)
    except Exception as e:
        print(e)
        sys.exit(1)