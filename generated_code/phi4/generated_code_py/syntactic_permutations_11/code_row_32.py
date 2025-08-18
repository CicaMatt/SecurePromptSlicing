def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of bounds")

def main():
    import sys
    
    id_sequence = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    
    try:
        index_input = int(input().strip())
        result = getValueFromArray(id_sequence, len(id_sequence), index_input)
        sys.exit(result)
    except (ValueError, IndexError):
        sys.exit(1)

if __name__ == "__main__":
    main()