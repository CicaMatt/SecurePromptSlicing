import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of bounds")

def main():
    try:
        id_sequence = [10, 20, 30, 40, 50]  # Example array
        index_to_fetch = int(sys.stdin.read().strip())
        result = getValueFromArray(id_sequence, len(id_sequence), index_to_fetch)
        sys.exit(result)
    except (ValueError, IndexError) as e:
        print(e, file=sys.stderr)
        sys.exit(1)

if __name__ == "__main__":
    main()