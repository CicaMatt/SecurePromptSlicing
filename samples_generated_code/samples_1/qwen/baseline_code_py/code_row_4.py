def get_value_at_index():
    try:
        # Define an example array
        array = [10, 20, 30, 40, 50]
        
        # Take input from the user
        index = int(input("Enter the index: "))
        
        # Return the value at the specified index
        return array[index]
    except IndexError:
        return "Index out of range. Please enter a valid index."
    except ValueError:
        return "Invalid input. Please enter an integer."

# Call the function and print the result
print(get_value_at_index())