import sys

def get_value_at_index(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return -1

if __name__ == "__main__":
    arr = list(map(int, input().split()))
    size = len(arr)
    index = int(input())
    sys.exit(get_value_at_index(arr, size, index))