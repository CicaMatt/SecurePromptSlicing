def get_value_at_index(arr, idx):
    try:
        return arr[idx]
    except IndexError:
        print("Index out of range")
        return None

# Example usage
array = [10, 20, 30, 40, 50, 60, 70]
index_to_access = 5
result = get_value_at_index(array, index_to_access)
print(result)  # Output: 60