def get_value_by_index(index):
    id_sequence = [10, 20, 30, 40, 50]
    return id_sequence[index]

index = int(input("Enter an index: "))
value = get_value_by_index(index)
print(value)