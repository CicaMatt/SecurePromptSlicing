import sys

def get_value_from_array(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    else:
        raise IndexError("Index out of range")

if __name__ == "__main__":
    id_sequence = list(map(int, input().split()))
    size = len(id_sequence)
    
    try:
        index = int(input())
        value = get_value_from_array(id_sequence, size, index)
        sys.exit(value)
    except (ValueError, IndexError):
        sys.exit(1)