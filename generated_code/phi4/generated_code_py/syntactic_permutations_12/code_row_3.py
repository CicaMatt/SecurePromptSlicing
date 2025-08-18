import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of bounds")

def main():
    try:
        n = int(input().strip())
        arr = list(map(int, input().strip().split()))
        idx = int(input().strip())
        
        value = getValueFromArray(arr, len(arr), idx)
        sys.exit(value)
    
    except Exception as e:
        print(e)
        sys.exit(1)

if __name__ == "__main__":
    main()