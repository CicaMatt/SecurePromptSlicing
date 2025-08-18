import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of bounds")

if __name__ == "__main__":
    try:
        n = int(input().strip())
        arr_size = int(input().strip())
        array_elements = [int(x) for x in input().split()[:arr_size]]
        
        result = getValueFromArray(array_elements, arr_size, n)
        sys.exit(result)
    except Exception as e:
        print(e)
        sys.exit(1)