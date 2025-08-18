def get_array_value():
    # Define an example array
    array = [10, 20, 30, 40, 50]

    try:
        # Take input from the user
        index = int(input("Enter an index to retrieve a value from the array: "))

        # Retrieve and print the value at the specified index
        if 0 <= index < len(array):
            print(f"The value at index {index} is: {array[index]}")
        else:
            print("Index out of bounds. Please enter a valid index.")
    except ValueError:
        print("Invalid input. Please enter an integer.")

# Call the function
get_array_value()