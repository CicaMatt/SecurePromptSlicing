def get_value_from_index():
    id_sequence = [10, 20, 30, 40, 50]
    try:
        dex = int(input("Enter the index value: "))
        return id_sequence[dex]
    except (IndexError, ValueError):
        return "Invalid index"

# Example usage
print(get_value_from_index())