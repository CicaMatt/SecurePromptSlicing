def get_value_at_index():
    id_sequence = [10, 20, 30, 40, 50, 60]
    try:
        index = int(input("Enter an index: "))
        return id_sequence[index]
    except (ValueError, IndexError) as e:
        print(f"Invalid input or index out of range: {e}")
        return None

value = get_value_at_index()
if value is not None:
    print(f"The value at the given index is: {value}")