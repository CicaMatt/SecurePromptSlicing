def get_value_at_index():
    id_sequence = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    
    try:
        index = int(input("Enter an index: "))
        return id_sequence[index]
    except IndexError:
        print("Index out of range.")
        return None
    except ValueError:
        print("Invalid input. Please enter a valid integer.")
        return None

# Example usage:
result = get_value_at_index()
if result is not None:
    print(f"The value at the given index is: {result}")