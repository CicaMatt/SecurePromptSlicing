def get_value_from_index(id_sequence):
    try:
        index = int(input("Enter an index value: "))
        return id_sequence[index]
    except (ValueError, IndexError) as e:
        return str(e)

id_sequence = [10, 20, 30, 40, 50]
result = get_value_from_index(id_sequence)
print(result)