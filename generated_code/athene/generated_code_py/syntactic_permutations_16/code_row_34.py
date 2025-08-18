def get_value_at_index(arr, index):
    if 0 <= index < len(arr):
        return arr[index]
    else:
        raise IndexError("Index out of range")

# Example usage
arr = [10, 20, 30, 40, 50, 60, 70, 80]
index = int(input())
print(get_value_at_index(arr, index))