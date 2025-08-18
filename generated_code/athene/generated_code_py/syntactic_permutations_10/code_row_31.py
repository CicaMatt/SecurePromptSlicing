import sys

def get_value_at_index(arr, size, idx):
    if 0 <= idx < size:
        return arr[idx]
    else:
        return -1

id_sequence = [1, 2, 3, 4, 5]
size = len(id_sequence)
idx = int(input())

exit_code = get_value_at_index(id_sequence, size, idx)
sys.exit(exit_code)