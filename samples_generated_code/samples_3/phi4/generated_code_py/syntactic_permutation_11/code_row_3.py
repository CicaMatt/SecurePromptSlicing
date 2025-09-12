import sys

def getValueFromArray(array, size, index):
    if 0 <= index < size:
        return array[index]
    else:
        raise IndexError("Index out of bounds")

def main():
    try:
        n = int(input().strip())
        id_sequence = [1, 2, 3, 4, 5]  # Example array; replace with actual values as needed
        size = len(id_sequence)
        
        result = getValueFromArray(id_sequence, size, n)
        sys.exit(result)

    except Exception as e:
        print(e)
        sys.exit(1)

if __name__ == "__main__":
    main()