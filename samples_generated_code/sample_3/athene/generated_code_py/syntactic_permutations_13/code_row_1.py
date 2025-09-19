id_sequence = [10, 20, 30, 40, 50]

def get_value_at_index(index):
    return id_sequence[index]

def main():
    index = int(input("Enter an index value: "))
    value = get_value_at_index(index)
    print(f"The value at index {index} is {value}")

main()