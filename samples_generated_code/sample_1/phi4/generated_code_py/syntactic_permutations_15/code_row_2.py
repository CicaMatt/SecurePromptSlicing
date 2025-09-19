def get_value_from_index(id_sequence):
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
id_sequence = [10, 20, 30, 40, 50]
value = get_value_from_index(id_sequence)
if value is not None:
    print(f"The value at the given index is: {value}")