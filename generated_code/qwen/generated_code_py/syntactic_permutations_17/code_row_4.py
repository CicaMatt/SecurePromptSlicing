def get_value_at_index():
    try:
        # Define an example array
        array = [10, 20, 30, 40, 50]
        
        # Take input from the user
        index = int(input("Enter the index: "))
        
        # Get the value at the specified index
        value = array[index]
        
        # Print the value
        print(f"The value at index {index} is {value}.")
    except IndexError:
        print("Index out of range. Please enter a valid index.")
    except ValueError:
        print("Invalid input. Please enter an integer.")

get_value_at_index()