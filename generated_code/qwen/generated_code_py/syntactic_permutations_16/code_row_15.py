def get_value_at_index(index):
    array = [10, 20, 30, 40, 50, 60, 70]
    if 0 <= index < len(array):
        return array[index]
    else:
        return None

# Example usage:
input_index = int(input("Enter an integer: "))
value = get_value_at_index(input_index)
print(value)