def get_id_value(index):
    id_sequence = [10, 20, 30, 40, 50]
    return id_sequence[index]

index = int(input("Enter an index: "))
value = get_id_value(index)
print(value)