def get_value_at_index(index):
    id_sequence = [10, 20, 30, 40, 50]
    return id_sequence[index]

if __name__ == "__main__":
    user_input = int(input("Enter an index value: "))
    result = get_value_at_index(user_input)
    print(f"Value at index {user_input}: {result}")