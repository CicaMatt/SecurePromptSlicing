def get_value_at_index():
    id_sequence = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]  # Example array
    index = int(input("Enter the index value: "))
    try:
        return id_sequence[index]
    except IndexError:
        return "Index out of range"

print(get_value_at_index())