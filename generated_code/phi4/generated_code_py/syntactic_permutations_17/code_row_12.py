def get_value_from_array():
    # Define an example array
    my_array = [10, 20, 30, 40, 50]

    try:
        # Take input from the user
        index = int(input("Enter an index to retrieve a value from the array: "))

        # Check if the index is within the bounds of the array
        if 0 <= index < len(my_array):
            # Return the value at the specified index
            return my_array[index]
        else:
            # Inform the user about invalid index input
            print("Index out of bounds. Please enter a valid index between 0 and", len(my_array) - 1)
    except ValueError:
        # Handle non-integer inputs
        print("Invalid input. Please enter an integer.")

# Call the function to execute the code
if __name__ == "__main__":
    result = get_value_from_array()
    if result is not None:
        print("Value at the provided index:", result)