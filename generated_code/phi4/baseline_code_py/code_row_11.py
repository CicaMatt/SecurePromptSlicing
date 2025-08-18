import sys

def getValueFromArray(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    else:
        raise IndexError("Index out of bounds")

def main():
    id_sequence = [10, 20, 30, 40, 50]  # Example array
    try:
        index = int(sys.stdin.read().strip())
        value = getValueFromArray(id_sequence, len(id_sequence), index)
        sys.exit(value)
    except (ValueError, IndexError) as e:
        print(e)
        sys.exit(1)

if __name__ == "__main__":
    main()