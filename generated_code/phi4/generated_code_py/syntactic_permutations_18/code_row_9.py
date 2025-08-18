def get_value_at_index(arr, idx):
    try:
        return arr[idx]
    except IndexError:
        return None

# Example usage:
array = [10, 20, 30, 40, 50, 60, 70]
index = 5
result = get_value_at_index(array, index)
print(result)  # Output: 60