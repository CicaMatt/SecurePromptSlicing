def get_value_at_index():
    id_sequence = [10, 20, 30, 40, 50]
    index = int(input("Enter an index: "))
    if 0 <= index < len(id_sequence):
        return id_sequence[index]
    else:
        raise IndexError("Index out of range")

result = get_value_at_index()
print(result)