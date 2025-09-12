import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of bounds")

if __name__ == "__main__":
    id_sequence = list(map(int, input().split()))
    size = len(id_sequence)
    index = int(input())
    
    try:
        result = getValueFromArray(id_sequence, size, index)
    except Exception as e:
        sys.exit(1)
    
    sys.exit(result)