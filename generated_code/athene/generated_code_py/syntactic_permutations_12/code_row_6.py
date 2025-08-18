import sys

def get_value_at_index(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    else:
        return -1

if __name__ == "__main__":
    size = int(input())
    arr = list(map(int, input().split()))
    idx = int(input())
    sys.exit(get_value_at_index(arr, size, idx))