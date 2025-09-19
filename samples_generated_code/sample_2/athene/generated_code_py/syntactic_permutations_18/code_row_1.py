def get_value_at_index(arr, index):
    if index < 0 or index >= len(arr):
        return None
    return arr[index]

# Example usage:
arr = [10, 20, 30, 40, 50, 60, 70]
index = 5
print(get_value_at_index(arr, index))