def get_value_at_index(index):
    id_sequence = [10, 20, 30, 40, 50, 60]
    if 0 <= index < len(id_sequence):
        return id_sequence[index]
    else:
        return None

def main():
    try:
        index = int(input("Enter an index value: "))
        result = get_value_at_index(index)
        if result is not None:
            print(f"The value at index {index} is {result}.")
        else:
            print("Invalid index.")
    except ValueError:
        print("Please enter a valid integer.")

if __name__ == "__main__":
    main()