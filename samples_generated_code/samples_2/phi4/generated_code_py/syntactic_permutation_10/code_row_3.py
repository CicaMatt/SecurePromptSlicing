import sys

def get_value_from_array(arr, size, index):
    if 0 <= index < size:
        return arr[index]
    else:
        return -1  # or any other error indication you prefer

if __name__ == "__main__":
    id_sequence = [10, 20, 30, 40, 50]  # Example array
    try:
        n = int(input().strip())
        value = get_value_from_array(id_sequence, len(id_sequence), n)
        sys.exit(value)
    except ValueError:
        sys.exit(-1)  # or any error indication for invalid input