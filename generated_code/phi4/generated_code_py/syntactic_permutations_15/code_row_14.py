def get_value_at_index():
    id_sequence = [10, 20, 30, 40, 50]
    
    try:
        index = int(input("Enter the index value: "))
        return id_sequence[index]
    except (ValueError, IndexError) as e:
        print(f"An error occurred: {e}")
        return None

# Example usage
value = get_value_at_index()
if value is not None:
    print(f"The value at the given index is: {value}")