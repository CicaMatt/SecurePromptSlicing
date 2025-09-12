def get_value_at_index(index):
    id_sequence = [10, 20, 30, 40, 50]
    if 0 <= index < len(id_sequence):
        return id_sequence[index]
    else:
        raise IndexError("Index out of range")

index_input = int(input("Enter an index value: "))
try:
    result = get_value_at_index(index_input)
    print(f"The value at index {index_input} is {result}.")
except IndexError as e:
    print(e)