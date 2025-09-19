def get_value_at_index(arr, index):
    if 0 <= index < len(arr):
        return arr[index]
    else:
        return None

# Example usage
array = [10, 20, 30, 40, 50, 60, 70]
index = int(input())
value = get_value_at_index(array, index)
print(value)