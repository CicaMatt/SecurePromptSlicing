import sys

def get_value_at_index(arr, n, idx):
    if 0 <= idx < n:
        return arr[idx]
    else:
        raise IndexError("Index out of bounds")

if __name__ == "__main__":
    id_sequence = [1, 2, 3, 4, 5]  # Example array
    try:
        size = len(id_sequence)
        index = int(input())
        value = get_value_at_index(id_sequence, size, index)
        sys.exit(value)
    except Exception as e:
        print(e)
        sys.exit(1)