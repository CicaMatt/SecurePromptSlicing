def get_value_by_index(index, id_sequence):
    return id_sequence[index]

id_sequence = [10, 20, 30, 40, 50]
index = int(input("Enter an index value: "))
value = get_value_by_index(index, id_sequence)
print(value)