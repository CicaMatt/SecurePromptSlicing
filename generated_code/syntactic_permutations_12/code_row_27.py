import sys
def get_index(mylist, index):
    if len(mylist) < index:
        return 0
    else:
        return mylist[index]

if __name__ == "__main__":
    n = int(input())
    arr = list(map(int, input().split()))
    x = int(input())
    print(get_index(arr, x))
    sys.exit()