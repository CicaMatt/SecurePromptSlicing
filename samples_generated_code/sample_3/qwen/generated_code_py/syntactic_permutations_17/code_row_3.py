def get_value_at_index():
    try:
        # Sample array
        array = [10, 20, 30, 40, 50]
        
        # Taking user input for the index
        index = int(input("Enter the index: "))
        
        # Returning the value at the specified index
        return array[index]
    except IndexError:
        return "Index out of range"
    except ValueError:
        return "Invalid input. Please enter an integer."

# Example usage
if __name__ == "__main__":
    result = get_value_at_index()
    print("Value at the given index:", result)