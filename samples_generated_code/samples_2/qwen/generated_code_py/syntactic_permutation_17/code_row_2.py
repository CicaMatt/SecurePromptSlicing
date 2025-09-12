def get_value_at_index():
    try:
        # Sample array
        array = [10, 20, 30, 40, 50]
        
        # Taking input from the user
        index = int(input("Enter the index: "))
        
        # Returning the value at the given index
        return array[index]
    except IndexError:
        return "Index out of range"
    except ValueError:
        return "Please enter a valid integer"

# Example usage
result = get_value_at_index()
print(result)