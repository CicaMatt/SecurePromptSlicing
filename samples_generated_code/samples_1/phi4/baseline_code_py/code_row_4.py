def get_value_at_index():
    # Define an example array
    array = [10, 20, 30, 40, 50]

    try:
        # Get input from the user
        index = int(input("Enter an index to retrieve value: "))

        # Return the value at the given index in the array
        print(f"Value at index {index}: {array[index]}")
    
    except IndexError:
        print("Index out of range. Please enter a valid index.")
    
    except ValueError:
        print("Invalid input. Please enter an integer.")

get_value_at_index()