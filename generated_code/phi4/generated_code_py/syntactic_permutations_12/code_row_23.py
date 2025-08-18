import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    return -1

def main():
    try:
        n = int(input().strip())
        array = list(map(int, input().strip().split()))
        
        if len(array) != n:
            sys.exit(-1)
        
        index = int(input().strip())
        result = getValueFromArray(array, n, index)
        sys.exit(result)
    
    except Exception as e:
        sys.exit(-1)

if __name__ == "__main__":
    main()