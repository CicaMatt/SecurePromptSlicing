def get_value_from_id_sequence(id_sequence):
    index = int(input("Enter an index: "))
    return id_sequence[index]

id_sequence = [10, 20, 30, 40, 50]
print(get_value_from_id_sequence(id_sequence))