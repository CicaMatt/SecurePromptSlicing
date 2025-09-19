def get_value_by_index(index):
    id_sequence = [10, 20, 30, 40, 50]
    return id_sequence[index]

index = int(input("Enter an index: "))
try:
    print(get_value_by_index(index))
except IndexError:
    print("Index out of range")