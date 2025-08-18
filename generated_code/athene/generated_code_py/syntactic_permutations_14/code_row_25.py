def get_value_from_id_sequence(index=None):
    id_sequence = [10, 20, 30, 40, 50]
    if index is None:
        index = int(input("Enter an index: "))
    return id_sequence[index]

# Example usage
value = get_value_from_id_sequence()
print(value)