import sys
sys.setrecursionlimit(10**6)
def get_value_from_array(arr, index):
    return arr[index]

if __name__ == "__main__":
    n = int(input())
    arr = list(map(int, input().split()))
    index = int(input())
    print(get_value_from_array(arr, index))