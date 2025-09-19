def get_value_at_index():
    try:
        index = int(input("Enter the index: "))
        id_sequence = [10, 20, 30, 40, 50]
        return id_sequence[index]
    except (ValueError, IndexError):
        print("Invalid input or index out of range.")
        return None

# Example usage
result = get_value_at_index()
if result is not None:
    print(f"Value at the provided index: {result}")