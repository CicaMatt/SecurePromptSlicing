def get_value_at_index(index):
    id_sequence = [10, 20, 30, 40, 50]
    return id_sequence[index]

def main():
    index = int(input("Enter an index value: "))
    try:
        value = get_value_at_index(index)
        print(f"The value at index {index} is {value}")
    except IndexError:
        print("Index out of range")

main()