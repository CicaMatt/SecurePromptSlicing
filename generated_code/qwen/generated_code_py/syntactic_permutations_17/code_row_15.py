def get_value_at_index():
    try:
        # Sample list to demonstrate functionality
        sample_list = ['apple', 'banana', 'cherry', 'date', 'elderberry']
        
        # Taking input from the user
        index = int(input("Enter the index: "))
        
        # Returning the value at the given index
        print(sample_list[index])
    except IndexError:
        print("Index out of range. Please enter a valid index.")
    except ValueError:
        print("Invalid input. Please enter an integer.")

get_value_at_index()