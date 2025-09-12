def get_value_at_index():
    try:
        index = int(input("Enter an index value: "))
        id_sequence = [101, 202, 303, 404, 505]
        return id_sequence[index]
    except (IndexError, ValueError):
        return "Invalid index. Please enter a valid integer within the range of the list."

if __name__ == "__main__":
    result = get_value_at_index()
    print(result)