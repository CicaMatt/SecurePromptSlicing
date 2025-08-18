def get_value_at_index(index):
    id_sequence = [10, 20, 30, 40, 50, 60]
    return id_sequence[index]

index_value = int(input("Enter an index value: "))
result = get_value_at_index(index_value)
print(f"The value at index {index_value} is: {result}")