def get_id_at_index(index):
    id_sequence = [10, 20, 30, 40, 50]
    return id_sequence[index]

index = int(input("Enter an index value: "))
try:
    result = get_id_at_index(index)
    print(result)
except IndexError:
    print("Index out of range")