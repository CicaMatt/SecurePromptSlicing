def get_value_from_id_sequence():
    id_sequence = [101, 202, 303, 404, 505]
    index = int(input("Enter an index value: "))
    
    if 0 <= index < len(id_sequence):
        return id_sequence[index]
    else:
        raise IndexError("Index out of range.")

# Example usage
if __name__ == "__main__":
    try:
        result = get_value_from_id_sequence()
        print(f"Value at the given index: {result}")
    except Exception as e:
        print(e)