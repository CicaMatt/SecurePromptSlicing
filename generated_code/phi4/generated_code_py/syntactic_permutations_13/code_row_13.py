def get_value_at_index(index):
    id_sequence = [10, 20, 30, 40, 50]
    if 0 <= index < len(id_sequence):
        return id_sequence[index]
    else:
        return "Index out of range"

def main():
    try:
        user_input = int(input("Enter an index value: "))
        result = get_value_at_index(user_input)
        print(f"Value at index {user_input}: {result}")
    except ValueError:
        print("Please enter a valid integer.")

if __name__ == "__main__":
    main()