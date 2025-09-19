def get_value_at_index():
    try:
        # Sample array
        array = [10, 20, 30, 40, 50]
        
        # Taking input from the user
        index = int(input("Enter the index: "))
        
        # Returning the value at the given index
        print(f"Value at index {index}: {array[index]}")
    except IndexError:
        print("Index out of range.")
    except ValueError:
        print("Please enter a valid integer.")

get_value_at_index()