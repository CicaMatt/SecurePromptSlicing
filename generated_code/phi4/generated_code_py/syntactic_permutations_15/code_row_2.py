def get_value_from_index():
    id_sequence = [10, 20, 30, 40, 50, 60, 70]
    try:
        index = int(input("Enter the index value: "))
        return id_sequence[index]
    except (ValueError, IndexError) as e:
        print(f"Error: {e}")
        return None

print(get_value_from_index())