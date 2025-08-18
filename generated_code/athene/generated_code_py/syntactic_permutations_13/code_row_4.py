def get_value_at_index(index, id_sequence):
    return id_sequence[index]

id_sequence = [10, 20, 30, 40, 50]

index = int(input("Enter an index value: "))
try:
    print(get_value_at_index(index, id_sequence))
except IndexError:
    print("Index out of range")