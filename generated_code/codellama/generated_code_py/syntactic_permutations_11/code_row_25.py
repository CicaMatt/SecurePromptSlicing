import sys

def getValueFromArray(arr, arr_size, index):
    if (index >= 0) and (index < arr_size):
        return arr[index]
    else:
        return -1

if __name__ == "__main__":
    n = int(input())
    if n > 0:
        arr = []
        for i in range(n):
            arr.append(int(input()))
        m = int(input())
        if (m >= 0) and (m < n):
            print(getValueFromArray(arr, n, m))
        else:
            print("-1")
    else:
        print("Invalid input!")