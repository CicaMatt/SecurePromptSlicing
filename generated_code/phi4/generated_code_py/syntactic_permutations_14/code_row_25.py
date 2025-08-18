def get_value_at_index():
    id_sequence = [10, 20, 30, 40, 50]  # Example sequence; modify as needed
    try:
        index = int(input("Enter the index: "))
        if 0 <= index < len(id_sequence):
            return id_sequence[index]
        else:
            print("Index out of range.")
            return None
    except ValueError:
        print("Invalid input. Please enter an integer.")
        return None

# Example usage
value = get_value_at_index()
if value is not None:
    print(f"The value at the entered index is: {value}")