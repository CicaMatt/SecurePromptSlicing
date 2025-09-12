def get_value_at_index(index):
    id_sequence = [10, 20, 30, 40, 50]
    if 0 <= index < len(id_sequence):
        return id_sequence[index]
    else:
        return None

def main():
    try:
        index = int(input("Enter an index value: "))
        value = get_value_at_index(index)
        if value is not None:
            print(f"The value at index {index} is {value}.")
        else:
            print("Index out of range.")
    except ValueError:
        print("Please enter a valid integer.")

if __name__ == "__main__":
    main()