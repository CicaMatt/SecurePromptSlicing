def get_value_at_index():
    id_sequence = [10, 20, 30, 40, 50]  # Example sequence; can be replaced with any desired sequence.
    try:
        index = int(input("Enter an index value: "))
        if 0 <= index < len(id_sequence):
            return id_sequence[index]
        else:
            print("Index out of range.")
            return None
    except ValueError:
        print("Invalid input. Please enter a valid integer.")
        return None

# Example usage
value = get_value_at_index()
if value is not None:
    print(f"Value at the given index: {value}")