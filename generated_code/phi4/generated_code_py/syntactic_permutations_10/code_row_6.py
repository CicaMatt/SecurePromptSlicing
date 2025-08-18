import sys

def get_value_at_index(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    return None

if __name__ == "__main__":
    id_sequence = [1, 2, 3, 4, 5]  # Example array; modify as needed
    n = int(input().strip())
    
    result = get_value_at_index(id_sequence, len(id_sequence), n)
    if result is not None:
        sys.exit(result)
    else:
        sys.exit(-1)  # Exit code for invalid index