def get_value_at_index():
    try:
        # User input
        index = int(input("Enter an index to retrieve the element at that position: "))
        
        # A sample list for demonstration purposes
        my_list = [10, 20, 30, 40, 50]

        # Check if the index is within bounds of the list
        if 0 <= index < len(my_list):
            print(f"The value at index {index} is {my_list[index]}")
        else:
            print("Index out of range.")
    except ValueError:
        print("Invalid input. Please enter a valid integer.")

# Call the function to execute the code
get_value_at_index()