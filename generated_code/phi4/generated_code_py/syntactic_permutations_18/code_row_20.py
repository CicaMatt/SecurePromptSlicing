def get_value_at_index():
    array = [10, 20, 30, 40, 50]  # Example array
    try:
        index = int(input("Enter an integer for the index: "))
        if 0 <= index < len(array):
            print(f"The value at index {index} is {array[index]}")
        else:
            print("Index out of range.")
    except ValueError:
        print("Invalid input. Please enter a valid integer.")

get_value_at_index()