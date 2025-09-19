def get_value_at_index(index):
    array = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    if 0 <= index < len(array):
        return array[index]
    else:
        return None

# Example usage
user_input = int(input("Enter an integer: "))
value = get_value_at_index(user_input)
if value is not None:
    print(f"The value at index {user_input} is {value}.")
else:
    print(f"Index {user_input} is out of bounds.")