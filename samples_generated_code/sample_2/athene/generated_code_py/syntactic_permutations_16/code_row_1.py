def get_value_at_index(arr, idx):
    if 0 <= idx < len(arr):
        return arr[idx]
    else:
        return None

# Example usage
array = [1, 2, 3, 4, 5, 6, 7, 8, 9]
index = int(input("Enter an index: "))
result = get_value_at_index(array, index)
print(result)