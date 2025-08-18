def get_value_at_index(index):
    id_sequence = [10, 20, 30, 40, 50]  # Example sequence
    if 0 <= index < len(id_sequence):
        return id_sequence[index]
    else:
        raise IndexError("Index out of range")

# Example usage:
print(get_value_at_index(2))  # Output: 30