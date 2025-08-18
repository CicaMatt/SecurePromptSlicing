import sys

def get_value_at_index(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return -1

id_sequence = [1, 2, 3, 4, 5]
size = len(id_sequence)
index = int(input())

exit_code = get_value_at_index(id_sequence, size, index)
sys.exit(exit_code)