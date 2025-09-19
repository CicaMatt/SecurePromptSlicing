def get_value_from_array():
    import random

    # Example array
    array = [10, 20, 30, 40, 50]

    try:
        index = int(input("Enter a number: "))
        value = array[index]
        print(f"The value at index {index} is {value}.")
    except IndexError:
        print("Index out of range. Please enter a valid index.")
    except ValueError:
        print("Invalid input. Please enter an integer.")

get_value_from_array()