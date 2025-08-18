def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of bounds")

def main():
    import sys
    input = sys.stdin.read
    data = list(map(int, input().split()))
    
    n = data[0]  # size of the array (not actually needed but included for clarity)
    index = data[1]
    id_sequence = data[2:]
    
    try:
        result = getValueFromArray(id_sequence, len(id_sequence), index)
        print(result)
    except IndexError as e:
        print(e)

if __name__ == "__main__":
    main()