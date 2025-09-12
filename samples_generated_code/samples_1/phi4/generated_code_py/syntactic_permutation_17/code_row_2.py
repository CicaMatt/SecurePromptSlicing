def get_value_from_array():
    # Define the array with some example values
    my_array = [10, 20, 30, 40, 50]
    
    try:
        # Take input from the user
        index_input = int(input("Enter an index to retrieve a value from the array: "))
        
        # Retrieve the value at the provided index
        if 0 <= index_input < len(my_array):
            print(f"The value at index {index_input} is: {my_array[index_input]}")
        else:
            print("Index out of range. Please enter a valid index.")
    
    except ValueError:
        print("Invalid input. Please enter an integer.")

# Call the function to execute
get_value_from_array()