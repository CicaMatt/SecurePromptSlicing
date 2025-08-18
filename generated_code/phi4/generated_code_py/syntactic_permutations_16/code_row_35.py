def get_value_at_index():
    lst = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]  # Example list; modify as needed

    try:
        user_input = int(input("Enter an integer index: "))
        value = lst[user_input]
        print(f"The value at index {user_input} is: {value}")
    except IndexError:
        print("Index out of range.")
    except ValueError:
        print("Invalid input. Please enter a valid integer.")

get_value_at_index()