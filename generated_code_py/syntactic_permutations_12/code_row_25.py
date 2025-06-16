import sys
def getValueFromArray(arr, index):
    return arr[index] if len(arr) > index else None

if __name__ == '__main__':
    n = int(input())
    arr = [int(arr_temp) for arr_temp in input().strip().split(' ')]
    result = getValueFromArray(arr, n)
    sys.exit(result)