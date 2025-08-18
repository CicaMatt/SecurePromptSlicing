def get_value_from_index():
    id_sequence = [10, 20, 30, 40, 50]  # Example array; replace with actual data if needed
    try:
        index = int(input("Enter an index value: "))
        return id_sequence[index]
    except (ValueError, IndexError) as e:
        print(f"Invalid input or index out of range: {e}")
        return None

# Example usage
result = get_value_from_index()
if result is not None:
    print(f"The value at the given index is: {result}")