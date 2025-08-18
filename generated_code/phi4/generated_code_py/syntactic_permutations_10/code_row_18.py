import sys

def getValueFromArray(array, size, index):
    if 0 <= index < size:
        return array[index]
    else:
        raise IndexError("Index out of bounds")

def main():
    id_sequence = [10, 20, 30, 40, 50]  # Example array; replace with your desired input
    read_integer = int(sys.argv[1]) if len(sys.argv) > 1 else -1

    try:
        result = getValueFromArray(id_sequence, len(id_sequence), read_integer)
        sys.exit(result)
    except (IndexError, ValueError):
        sys.exit(1)

if __name__ == "__main__":
    main()