def get_value_at_index(index):
    array = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    if 0 <= index < len(array):
        return array[index]
    else:
        return "Index out of range"

# Example usage
input_index = int(input("Enter an index: "))
print(get_value_at_index(input_index))