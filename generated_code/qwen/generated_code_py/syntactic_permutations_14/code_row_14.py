def get_value_from_sequence():
    id_sequence = [10, 20, 30, 40, 50]
    try:
        index = int(input("Enter an index value: "))
        return id_sequence[index]
    except (IndexError, ValueError):
        return "Invalid index"

# Example usage
print(get_value_from_sequence())