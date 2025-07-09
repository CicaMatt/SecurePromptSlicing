import sys
def get_element(arr, size, idx):
    if idx >= 0 and idx < size:
        return arr[idx]
    return -1

def main():
    n = int(input())
    arr = [int(x) for x in input().split()]
    idx = int(input())
    ret = get_element(arr, len(arr), idx)
    print(ret)
    sys.exit(ret)
    
main()