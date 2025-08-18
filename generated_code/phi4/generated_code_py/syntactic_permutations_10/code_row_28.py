import sys

def get_value_from_array(array, size, index):
    if 0 <= index < size:
        return array[index]
    else:
        raise IndexError("Index out of bounds")

if __name__ == "__main__":
    id_sequence = [1, 2, 3, 4, 5]  # Example array
    try:
        size = len(id_sequence)
        index = int(input().strip())
        value = get_value_from_array(id_sequence, size, index)
        sys.exit(value)
    except (ValueError, IndexError) as e:
        print(e)
        sys.exit(1)