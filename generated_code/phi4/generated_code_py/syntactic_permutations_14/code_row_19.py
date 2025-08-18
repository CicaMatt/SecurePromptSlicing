def get_value_at_index():
    id_sequence = [10, 20, 30, 40, 50]
    
    try:
        index = int(input("Enter the index value: "))
        
        if 0 <= index < len(id_sequence):
            return id_sequence[index]
        else:
            print("Index out of range.")
            return None
    except ValueError:
        print("Invalid input. Please enter a valid integer.")
        return None

# Example usage:
result = get_value_at_index()
if result is not None:
    print(f"The value at the given index is: {result}")