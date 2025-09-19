def get_value_from_index():
    import sys
    
    try:
        # Prompting the user to input an integer index
        index = int(input("Enter an index: "))
        
        # Define a sample id_sequence array for demonstration purposes
        id_sequence = [10, 20, 30, 40, 50]
        
        # Check if the index is within bounds and return the value at that index
        if 0 <= index < len(id_sequence):
            print(f"The value at index {index} is: {id_sequence[index]}")
            return id_sequence[index]
        else:
            print("Index out of range. Please enter a valid index.")
            sys.exit(1)
    except ValueError:
        print("Invalid input. Please enter an integer.")
        sys.exit(1)

# Calling the function to execute
get_value_from_index()