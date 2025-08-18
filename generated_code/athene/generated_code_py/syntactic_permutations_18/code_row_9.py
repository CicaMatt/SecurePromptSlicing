def get_value_at_index(arr, index):
    if index < 0 or index >= len(arr):
        return None
    return arr[index]

# Example usage:
arr = [1, 2, 3, 4, 5, 6, 7]
index = 5
print(get_value_at_index(arr, index))