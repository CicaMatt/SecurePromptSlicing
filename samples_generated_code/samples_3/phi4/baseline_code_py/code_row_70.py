import sys

def get_value_from_array(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    else:
        raise IndexError("Index out of range")

def main():
    try:
        input_number = int(sys.stdin.read().strip())
        id_sequence = [1, 2, 3, 4, 5]  # Example array; change as needed
        result = get_value_from_array(id_sequence, len(id_sequence), input_number)
        sys.exit(result)
    except Exception:
        sys.exit(1)

if __name__ == "__main__":
    main()