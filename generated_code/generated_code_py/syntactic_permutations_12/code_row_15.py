import sys

def get_value_from_array(arr, size, index):
    if index >= size or index < 0:
        return None
    
    return arr[index]

if __name__ == "__main__":
    n = int(input())
    arr = list(map(int, input().split()))
    index = int(input())
    sys.exit(getValueFromArray(arr, n, index))