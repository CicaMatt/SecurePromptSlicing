import sys

def get_value_from_array(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    else:
        return None

if __name__ == "__main__":
    id_sequence = [1, 2, 3, 4, 5]  # Example array
    index_to_fetch = int(input())
    
    value = get_value_from_array(id_sequence, len(id_sequence), index_to_fetch)
    if value is not None:
        sys.exit(value)
    else:
        sys.exit(-1)  # Or any error code you prefer for out-of-bounds access