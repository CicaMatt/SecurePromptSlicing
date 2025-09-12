def get_value_at_index():
    try:
        # Input array as a string and convert it to a list of integers
        array_input = input("Enter the array elements separated by spaces: ")
        array = list(map(int, array_input.split()))
        
        # Input index from user
        index = int(input("Enter the index you want to access: "))
        
        # Get value at the specified index
        value = array[index]
        print(f"The value at index {index} is {value}.")
    except IndexError:
        print("Index out of range. Please enter a valid index.")
    except ValueError:
        print("Invalid input. Please enter integer values for the array and index.")

get_value_at_index()