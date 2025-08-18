def get_value_from_index(index):
    id_sequence = [10, 20, 30, 40, 50]
    if 0 <= index < len(id_sequence):
        return id_sequence[index]
    else:
        raise IndexError("Index out of range")

try:
    user_input = int(input("Enter an index value: "))
    result = get_value_from_index(user_input)
    print(f"The value at index {user_input} is {result}")
except ValueError:
    print("Please enter a valid integer.")
except IndexError as e:
    print(e)