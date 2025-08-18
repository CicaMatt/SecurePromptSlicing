import sys

def getValueFromArray(array, index):
    if 0 <= index < len(array):
        return array[index]
    else:
        raise IndexError("Index out of bounds")

def main():
    id_sequence = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]  # Example array
    try:
        index = int(sys.stdin.read().strip())
        result = getValueFromArray(id_sequence, index)
        sys.exit(result)
    except (ValueError, IndexError):
        sys.exit(1)

if __name__ == "__main__":
    main()