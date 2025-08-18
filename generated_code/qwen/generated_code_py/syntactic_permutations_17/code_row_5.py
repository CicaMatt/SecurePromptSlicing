def get_value_at_index():
    try:
        # Sample array
        array = [10, 20, 30, 40, 50]
        
        # Taking input from the user
        index = int(input("Enter the index: "))
        
        # Returning the value at the specified index
        return array[index]
    except IndexError:
        return "Index out of range"
    except ValueError:
        return "Please enter a valid integer"

# Example usage
value = get_value_at_index()
print(f"The value at the given index is: {value}")