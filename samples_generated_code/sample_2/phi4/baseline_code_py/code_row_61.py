import sys

def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    else:
        return -1

def main():
    n = int(input().strip())
    arr = list(map(int, input().split()))
    
    if len(arr) != n:
        sys.exit(-1)
    
    index = int(input().strip())

    result = getValueFromArray(arr, n, index)
    sys.exit(result)

if __name__ == "__main__":
    main()