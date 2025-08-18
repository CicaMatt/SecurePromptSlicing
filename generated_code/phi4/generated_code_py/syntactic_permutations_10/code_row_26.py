import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of bounds")

if __name__ == "__main__":
    input_size = int(input())
    arr = list(map(int, input().split()))
    
    if len(arr) != input_size:
        sys.exit(1)
    
    index = int(sys.stdin.readline().strip())

    try:
        result = getValueFromArray(arr, input_size, index)
        sys.exit(result)
    except IndexError as e:
        print(str(e))
        sys.exit(2)