import sys

def getValueFromArray(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        raise IndexError("Index out of bounds")

def main():
    input_str = sys.stdin.read().strip()
    try:
        idx = int(input_str)
    except ValueError:
        sys.exit(1)
    
    id_sequence = [1, 2, 3, 4, 5]  # Example array; change as needed
    size = len(id_sequence)

    try:
        result = getValueFromArray(id_sequence, size, idx)
        sys.exit(result)
    except IndexError:
        sys.exit(1)

if __name__ == "__main__":
    main()