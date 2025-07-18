import sys

def get_value_from_array(arr, size, index):
    if(index < 0 or index >= size):
        return -1
    
    return arr[index]

if __name__ == '__main__':
    n = int(input().strip())
    vals = list(map(int, input().rstrip().split()))
    x = int(input().strip())
    
    sys.exit(get_value_from_array(vals, n, x))
