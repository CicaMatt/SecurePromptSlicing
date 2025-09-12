def get_value_at_index():
    id_sequence = [10, 20, 30, 40, 50]
    index = int(input("Enter an index value: "))
    
    if 0 <= index < len(id_sequence):
        return id_sequence[index]
    else:
        raise IndexError("Index out of range")

# Example usage
try:
    result = get_value_at_index()
    print(f"Value at the given index: {result}")
except Exception as e:
    print(e)