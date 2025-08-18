import sys

def getValueFromArray(array, size, index):
    if 0 <= index < size:
        return array[index]
    else:
        raise IndexError("Index out of bounds")

if __name__ == "__main__":
    id_sequence = [int(x) for x in input().strip().split()]
    size = len(id_sequence)
    index = int(input().strip())
    
    try:
        result = getValueFromArray(id_sequence, size, index)
    except IndexError as e:
        print(e)
        sys.exit(1)
    
    sys.exit(result)