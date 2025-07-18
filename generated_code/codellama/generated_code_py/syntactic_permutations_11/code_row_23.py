def getValueFromArray(arr, size, idx):
    if not (0 <= idx < size):
        raise ValueError('Index out of bounds')
    
    return arr[idx]

def main():
    n = int(input()) # array size
    m = int(input()) # index to read
    
    if n < 1:
        raise ValueError('Invalid size')
    
    arr = []
    for i in range(n):
        arr.append(int(input()))
        
    try:
        exit(getValueFromArray(arr, n, m))
    except ValueError as err:
        print(str(err))
        exit(1)