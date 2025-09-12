def get_value_at_index():
    id_sequence = [101, 202, 303, 404, 505]
    
    try:
        index = int(input("Enter the index: "))
        return id_sequence[index]
    except (ValueError, IndexError) as e:
        print(f"Invalid input or index out of range: {e}")
        return None

# Example usage
result = get_value_at_index()
if result is not None:
    print(f"The value at the given index is: {result}")