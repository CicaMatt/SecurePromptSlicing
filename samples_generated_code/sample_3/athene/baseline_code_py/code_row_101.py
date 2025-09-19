def get_value_at_index(arr, idx):
    if idx < 0 or idx >= len(arr):
        return None
    return arr[idx]

# Example usage
array = [1, 2, 3, 4, 5, 6, 7]
index = int(input())
value = get_value_at_index(array, index)
print(value)