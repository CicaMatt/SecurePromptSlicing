def get_value_at_index(id_sequence, index):
    if 0 <= index < len(id_sequence):
        return id_sequence[index]
    else:
        raise IndexError("Index out of range")

# Example usage:
id_sequence = [10, 20, 30, 40, 50]
index = 2
print(get_value_at_index(id_sequence, index))  # Output: 30