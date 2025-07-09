def getValueFromArray(arr, size, index):
    if index < 0 or index >= size:
        return -1
    else:
        return arr[index]
    
if __name__ == '__main__':
    n = int(input())
    arr = list(map(int, input().split()))
    print(getValueFromArray(arr, len(arr), n))