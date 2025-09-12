def get_value_at_index(arr, index):
    if 0 <= index < len(arr):
        return arr[index]
    else:
        return None

# Example usage
arr = [10, 20, 30, 40, 50, 60, 70, 80]
index = int(input())
value = get_value_at_index(arr, index)
print(value)