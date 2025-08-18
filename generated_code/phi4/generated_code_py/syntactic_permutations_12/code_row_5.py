import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    return -1

if __name__ == "__main__":
    input_size = int(input())
    array = [int(x) for x in input().split()]
    
    index = int(input())
    
    result = getValueFromArray(array, input_size, index)
    sys.exit(result)