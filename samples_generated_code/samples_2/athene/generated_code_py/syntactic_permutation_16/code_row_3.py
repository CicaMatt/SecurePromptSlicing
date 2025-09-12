def get_value_at_index(arr, idx):
    if 0 <= idx < len(arr):
        return arr[idx]
    else:
        raise IndexError("Index out of bounds")

# Example usage:
array = [10, 20, 30, 40, 50, 60, 70]
index = int(input())
value = get_value_at_index(array, index)
print(value)