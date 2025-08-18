import sys

def get_value_at_index(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    else:
        return -1

if __name__ == "__main__":
    id_sequence = [1, 2, 3, 4, 5]  # Example array
    size = len(id_sequence)
    index = int(input())
    exit_code = get_value_at_index(id_sequence, size, index)
    sys.exit(exit_code)