def get_value_at_index(id_sequence):
    index = int(input("Enter the index: "))
    return id_sequence[index]

# Example usage
id_sequence = [10, 20, 30, 40, 50]
value = get_value_at_index(id_sequence)
print(f"The value at the given index is: {value}")