def get_value_from_index():
    id_sequence = [10, 20, 30, 40, 50]
    
    try:
        index = int(input("Enter an index value: "))
        return id_sequence[index]
    except (ValueError, IndexError):
        print("Invalid index or input type.")
        return None

# Example usage
result = get_value_from_index()
if result is not None:
    print(f"Value at the given index: {result}")