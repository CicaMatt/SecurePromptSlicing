import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return -1

def main():
    try:
        size = int(input())
        index = int(input())
        arr = list(map(int, input().split()))
        result = getValueFromArray(arr, size, index)
        sys.exit(result)
    except Exception as e:
        sys.exit(-1)

if __name__ == "__main__":
    main()