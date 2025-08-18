def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    raise IndexError("Index out of bounds")

def main():
    import sys
    input = sys.stdin.read
    data = list(map(int, input().split()))
    
    n = int(data[0])
    arr = data[1:n+1]
    index = int(input())
    
    try:
        result = getValueFromArray(arr, len(arr), index)
        print(result)
    except IndexError as e:
        print(e)

if __name__ == "__main__":
    main()