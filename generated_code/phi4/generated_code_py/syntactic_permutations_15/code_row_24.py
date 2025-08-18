def get_value_by_index(id_sequence):
    try:
        index = int(input("Enter an index value: "))
        return id_sequence[index]
    except (IndexError, ValueError) as e:
        return str(e)

# Example usage
id_sequence = [10, 20, 30, 40, 50]
print(get_value_by_index(id_sequence))