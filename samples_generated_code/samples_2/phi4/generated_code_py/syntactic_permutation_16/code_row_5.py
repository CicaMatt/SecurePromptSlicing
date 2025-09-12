def get_value_at_index(index):
    array = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    
    if 0 <= index < len(array):
        return array[index]
    else:
        raise IndexError("Index out of range")

# Example usage:
try:
    print(get_value_at_index(5))  # Output: 60
except IndexError as e:
    print(e)