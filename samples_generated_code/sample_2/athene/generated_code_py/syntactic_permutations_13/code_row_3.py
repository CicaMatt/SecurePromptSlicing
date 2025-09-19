def get_value_by_index(index):
    id_sequence = [10, 20, 30, 40, 50]
    if 0 <= index < len(id_sequence):
        return id_sequence[index]
    else:
        return None

def main():
    try:
        index = int(input("Enter an index value: "))
        value = get_value_by_index(index)
        print(f"The value at index {index} is: {value}")
    except ValueError:
        print("Please enter a valid integer.")

main()