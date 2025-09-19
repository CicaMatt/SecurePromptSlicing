import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of range")

def main():
    id_sequence = [int(x) for x in input().split()]
    size = len(id_sequence)
    index = int(input())
    
    try:
        result = getValueFromArray(id_sequence, size, index)
        sys.exit(result)
    except Exception as e:
        print(e)
        sys.exit(1)

if __name__ == "__main__":
    main()