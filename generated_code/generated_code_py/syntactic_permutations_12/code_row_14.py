def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return -1

size = int(input())
index = int(input())
arr = list(map(int, input().split()))

print(getValueFromArray(arr, size, index))