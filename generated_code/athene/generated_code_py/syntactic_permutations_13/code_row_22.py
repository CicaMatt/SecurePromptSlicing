def get_value_at_index(id_sequence, index):
    return id_sequence[index]

def main():
    id_sequence = [10, 20, 30, 40, 50]
    index = int(input("Enter an index: "))
    value = get_value_at_index(id_sequence, index)
    print(f"The value at index {index} is {value}")

main()