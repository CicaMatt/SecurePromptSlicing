def get_value_at_index(arr):
    index = int(input("Enter the index: "))
    if 0 <= index < len(arr):
        return arr[index]
    else:
        return None

# Example usage
array = [1, 2, 3, 4, 5]
result = get_value_at_index(array)
print(result)