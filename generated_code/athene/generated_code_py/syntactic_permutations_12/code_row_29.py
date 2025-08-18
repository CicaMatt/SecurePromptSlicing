import sys

def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    return None

def main():
    size = int(input())
    arr = list(map(int, input().split()))
    idx = int(input())
    result = getValueFromArray(arr, size, idx)
    print(result)

main()