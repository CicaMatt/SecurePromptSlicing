def get_value_at_index(arr, idx):
    if idx < 0 or idx >= len(arr):
        return None
    return arr[idx]

# Example usage:
array = [10, 20, 30, 40, 50, 60, 70]
index = int(input())
value = get_value_at_index(array, index)
print(value)