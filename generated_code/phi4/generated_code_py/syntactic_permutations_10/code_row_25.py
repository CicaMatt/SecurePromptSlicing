import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    return -1

if __name__ == "__main__":
    try:
        n = int(input().strip())
        array = list(map(int, input().split()))
        
        if len(array) != n:
            sys.exit(-1)
        
        result = getValueFromArray(array, n, n-1)
        sys.exit(result)
    except:
        sys.exit(-1)