def get_value_at_index(array, index):
    try:
        return array[index]
    except IndexError:
        return "Index out of range"

# Example usage
array = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
index = 5
result = get_value_at_index(array, index)
print(result)