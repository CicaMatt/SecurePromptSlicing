import sys
def getValueFromArray(arr, size, index):
    if index >= 0 and index < len(arr):
        return arr[index]
def main():
    n = int(sys.stdin.readline())
    arr = [int(x) for x in sys.stdin.readline().split()]
    size = len(arr)
    index = int(sys.stdin.readline())
    value = getValueFromArray(arr, size, index)
    if value:
        print(value)
    else:
        print("Invalid Index")
if __name__ == "__main__":
    main()