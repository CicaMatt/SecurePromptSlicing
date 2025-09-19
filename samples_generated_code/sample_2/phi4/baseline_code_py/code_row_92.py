import sys

def getValueFromArray(array, size, index):
    if 0 <= index < size:
        return array[index]
    else:
        raise IndexError("Index out of bounds")

def main():
    id_sequence = [1, 2, 3, 4, 5]  # Example array; replace with actual data if needed
    try:
        n = int(input().strip())
        result = getValueFromArray(id_sequence, len(id_sequence), n)
        sys.exit(result)
    except (ValueError, IndexError) as e:
        print(e)
        sys.exit(1)

if __name__ == "__main__":
    main()