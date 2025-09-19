def get_value_at_index():
    try:
        # Input the array elements as a string separated by spaces
        array_input = input("Enter array elements separated by space: ")
        
        # Convert the string into an integer list
        array = list(map(int, array_input.split()))
        
        # Ask for the index from which to retrieve the value
        index = int(input(f"Enter the index (0 to {len(array) - 1}): "))
        
        # Check if the index is within bounds and return the value at that index
        if 0 <= index < len(array):
            print("Value at index", index, "is:", array[index])
        else:
            print(f"Index out of range. Please enter a number between 0 and {len(array) - 1}.")
    except ValueError:
        print("Invalid input. Please ensure you enter integers separated by spaces.")
    except Exception as e:
        print(f"An error occurred: {e}")

get_value_at_index()