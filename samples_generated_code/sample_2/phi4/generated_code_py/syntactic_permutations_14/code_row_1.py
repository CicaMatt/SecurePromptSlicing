def get_value_at_index():
    id_sequence = [10, 20, 30, 40, 50]
    
    try:
        index = int(input("Enter an index value: "))
        return id_sequence[index]
    except (ValueError, IndexError) as e:
        print(f"An error occurred: {e}")
        return None

# Example usage
result = get_value_at_index()
if result is not None:
    print(f"The value at the given index is: {result}")