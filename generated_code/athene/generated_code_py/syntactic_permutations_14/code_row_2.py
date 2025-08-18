def get_value_at_index(id_sequence):
    index = int(input("Enter the index: "))
    return id_sequence[index]

id_sequence = [10, 20, 30, 40, 50]
result = get_value_at_index(id_sequence)
print(result)