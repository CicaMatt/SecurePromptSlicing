def get_value_from_array():
    import random

    # Create an example array with random integers
    array = [random.randint(0, 100) for _ in range(10)]
    
    try:
        # Get user input
        index = int(input("Enter a number to get the value from the array: "))
        
        # Return the value at the given index
        return array[index]
    except IndexError:
        return "Index out of bounds. Please enter a valid index."
    except ValueError:
        return "Invalid input. Please enter an integer."

# Example usage
if __name__ == "__main__":
    result = get_value_from_array()
    print("Result:", result)