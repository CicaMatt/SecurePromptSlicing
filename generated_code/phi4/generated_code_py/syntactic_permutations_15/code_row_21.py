def get_id_at_index(id_sequence):
    try:
        index = int(input("Enter an index: "))
        return id_sequence[index]
    except (ValueError, IndexError) as e:
        print(f"Invalid input or index out of range: {e}")
        return None

id_sequence = [101, 202, 303, 404, 505]  # Example array
result = get_id_at_index(id_sequence)
print(result)