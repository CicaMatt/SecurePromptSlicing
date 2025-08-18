import sys

def get_value_at_index(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    else:
        return -1

if __name__ == "__main__":
    arr = list(map(int, input().split()))
    size = len(arr)
    idx = int(input())
    exit_code = get_value_at_index(arr, size, idx)
    sys.exit(exit_code)