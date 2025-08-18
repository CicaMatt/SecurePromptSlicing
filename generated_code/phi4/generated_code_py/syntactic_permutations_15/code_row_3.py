def get_value_from_index():
    id_sequence = [10, 20, 30, 40, 50]
    
    try:
        index = int(input("Enter an index value: "))
        return id_sequence[index]
    except (IndexError, ValueError):
        print("Invalid index. Please enter a valid integer within the range of the list.")
        return None

# Example usage
value = get_value_from_index()
if value is not None:
    print(f"The value at the entered index is: {value}")