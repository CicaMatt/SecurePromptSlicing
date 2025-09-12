def get_id_value(index):
    id_sequence = [10, 20, 30, 40, 50]
    if 0 <= index < len(id_sequence):
        return id_sequence[index]
    else:
        return None

def main():
    try:
        index = int(input("Enter an index value: "))
        value = get_id_value(index)
        print(f"The value at index {index} is: {value}")
    except ValueError:
        print("Invalid input. Please enter a numeric index.")

main()