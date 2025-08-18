def get_value_at_index(index, id_sequence):
    return id_sequence[index]

id_sequence = [10, 20, 30, 40, 50]
index = int(input("Enter an index: "))
try:
    result = get_value_at_index(index, id_sequence)
    print(f"The value at index {index} is {result}")
except IndexError:
    print("Index out of range")