def get_value_at_index(index):
    array = [10, 20, 30, 40, 50]
    if 0 <= index < len(array):
        return array[index]
    else:
        return "Index out of range"

# Example usage
input_index = int(input("Enter an integer: "))
result = get_value_at_index(input_index)
print(f"The value at index {input_index} is: {result}")