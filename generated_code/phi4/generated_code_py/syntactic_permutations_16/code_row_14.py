def get_value_at_index(input_index):
    my_array = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    
    if 0 <= input_index < len(my_array):
        return my_array[input_index]
    else:
        raise IndexError("Index out of range")

try:
    user_input = int(input("Enter an integer index: "))
    result = get_value_at_index(user_input)
    print(f"The value at index {user_input} is: {result}")
except ValueError:
    print("Please enter a valid integer.")
except IndexError as e:
    print(e)