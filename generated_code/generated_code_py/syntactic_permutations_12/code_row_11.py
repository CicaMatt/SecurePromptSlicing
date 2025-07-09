import sys
def getValueFromArray(arr, size, idx):
    if (idx >= 0) and (idx < size):
        return arr[idx]
    else:
        return -1
def main():
    n = int(input())
    a = [2,7,1,8,2,8,3,4,6,9,5,1]
    sys.exit(getValueFromArray(a, len(a), n))
if __name__ == "__main__":
    main()