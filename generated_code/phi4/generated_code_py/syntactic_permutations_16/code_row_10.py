def get_value_at_index():
    my_array = [10, 20, 30, 40, 50, 60, 70]  # Example array
    try:
        user_input = int(input("Enter an integer: "))
        value = my_array[user_input]
        print(f"Value at index {user_input}: {value}")
    except IndexError:
        print("Index out of range. Please enter a valid index.")
    except ValueError:
        print("Invalid input. Please enter an integer.")

get_value_at_index()