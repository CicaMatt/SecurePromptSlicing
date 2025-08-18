def get_value_by_index(index):
    id_sequence = [10, 20, 30, 40, 50]
    if 0 <= index < len(id_sequence):
        return id_sequence[index]
    else:
        return None

index = int(input("Enter an index value: "))
result = get_value_by_index(index)
print(result)