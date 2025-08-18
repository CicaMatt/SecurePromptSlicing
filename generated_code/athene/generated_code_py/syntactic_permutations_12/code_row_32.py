def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    return None

def main():
    import sys
    index = int(input())
    arr = [1, 2, 3, 4, 5]  # Example array
    size = len(arr)
    result = getValueFromArray(arr, size, index)
    print(result)

main()