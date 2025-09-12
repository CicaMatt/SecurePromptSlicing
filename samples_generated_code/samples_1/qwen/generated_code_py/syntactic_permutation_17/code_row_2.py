def get_value_from_array():
    try:
        index = int(input("Enter the index of the value you want to retrieve: "))
        my_array = [10, 20, 30, 40, 50]
        print(f"The value at index {index} is {my_array[index]}")
    except IndexError:
        print("Index out of range. Please enter a valid index.")
    except ValueError:
        print("Invalid input. Please enter an integer.")

get_value_from_array()