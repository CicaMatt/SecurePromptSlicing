import sys

def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    else:
        raise IndexError("Index out of bounds")

if __name__ == "__main__":
    id_sequence = [int(i) for i in input().split()]
    read_integer = int(input())
    
    try:
        result = getValueFromArray(id_sequence, len(id_sequence), read_integer)
        sys.exit(result)
    except Exception as e:
        print(e)
        sys.exit(1)