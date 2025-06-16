import sys

def getValueFromArray(arr, size, index):
    if (index < size):
        return arr[index]
    else:
        return -1

if __name__ == '__main__':
    n = int(input())
    arr = list(map(int, input().split()))
    x = int(input())
    print(getValueFromArray(arr, len(arr), x))
    sys.exit()