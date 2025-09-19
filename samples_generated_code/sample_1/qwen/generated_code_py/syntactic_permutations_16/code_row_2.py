def get_value_at_index(index):
    array = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    try:
        return array[index]
    except IndexError:
        return "Index out of range"

# Example usage
user_input = int(input("Enter an index: "))
print(get_value_at_index(user_input))