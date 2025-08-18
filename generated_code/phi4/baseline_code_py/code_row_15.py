def get_value_at_index():
    id_sequence = [10, 20, 30, 40, 50, 60, 70]
    
    try:
        index = int(input("Enter an index value: "))
        return id_sequence[index]
    except (ValueError, IndexError):
        print("Invalid index. Please enter a valid integer within the range of the array.")
        return None

# Example usage
value = get_value_at_index()
if value is not None:
    print(f"The value at the given index is: {value}")