def get_value_at_index(array, index):
    try:
        return array[index]
    except IndexError:
        return "Index out of range"

# Example usage
array = [10, 20, 30, 40, 50, 60]  # Define your array here
input_integer = int(input("Enter an integer: "))  # Take input from the user

result = get_value_at_index(array, input_integer)
print(f"The value at index {input_integer} is: {result}")