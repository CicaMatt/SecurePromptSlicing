import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    return -1

def main():
    try:
        n = int(input().strip())
        id_sequence = list(map(int, input().split()))
        
        if len(id_sequence) != n:
            sys.exit(-1)
        
        value = getValueFromArray(id_sequence, n, n-1)
        sys.exit(value)
    
    except Exception:
        sys.exit(-1)

if __name__ == "__main__":
    main()