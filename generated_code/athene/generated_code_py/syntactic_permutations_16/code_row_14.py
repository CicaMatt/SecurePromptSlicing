def get_value_at_index(arr, index):
    if 0 <= index < len(arr):
        return arr[index]
    else:
        return None

# Example usage
arr = [1, 2, 3, 4, 5, 6, 7, 8, 9]
index = int(input())
print(get_value_at_index(arr, index))