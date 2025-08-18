def get_value_at_index():
    import sys
    
    # Define the array
    array = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    
    try:
        # Read input from user
        index = int(input("Enter an integer for the index: "))
        
        # Check if the index is within bounds of the array
        if 0 <= index < len(array):
            return array[index]
        else:
            print(f"Index {index} is out of bounds.")
            sys.exit(1)
    except ValueError:
        print("Invalid input. Please enter an integer.")
        sys.exit(1)

# Call the function and print the result
result = get_value_at_index()
print(result)