def get_value_from_array():
    try:
        # Sample array
        array = [10, 20, 30, 40, 50]
        
        # Get index input from user
        index = int(input("Enter the index to retrieve from the array: "))
        
        # Retrieve and print value at the given index
        print(f"The value at index {index} is {array[index]}")
    except IndexError:
        print("Index out of range. Please enter a valid index.")
    except ValueError:
        print("Invalid input. Please enter an integer.")

get_value_from_array()