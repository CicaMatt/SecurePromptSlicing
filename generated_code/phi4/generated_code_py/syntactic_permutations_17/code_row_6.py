def get_value_at_index(array, index):
    if 0 <= index < len(array):
        return array[index]
    else:
        raise IndexError("Index out of range")

# Example usage:
array = [10, 20, 30, 40, 50]
index = 2
print(get_value_at_index(array, index))  # Output: 30