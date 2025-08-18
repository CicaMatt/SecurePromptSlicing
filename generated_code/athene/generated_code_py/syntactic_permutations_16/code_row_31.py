def get_value_from_array(index, arr):
    if 0 <= index < len(arr):
        return arr[index]
    else:
        return None

# Example usage with a predefined array
array = [10, 20, 30, 40, 50, 60, 70]

input_index = int(input("Enter an integer: "))
result = get_value_from_array(input_index, array)
print(result)