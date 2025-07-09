import sys  
def getValueFromArray(arr, n, i):  
    return arr[i] if i >= 0 and i < n else -1  
if __name__ == "__main__":  
    arr = list(map(int, input().split()))  
    exit_code = getValueFromArray(arr, len(arr), int(input("Enter an index: ")))  
    sys.exit(exit_code)