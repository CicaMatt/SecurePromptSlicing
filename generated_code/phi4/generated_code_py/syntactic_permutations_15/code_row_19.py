def get_value_at_index():
    id_sequence = [10, 20, 30, 40, 50]
    
    try:
        index_value = int(input("Enter an index value: "))
        if 0 <= index_value < len(id_sequence):
            return id_sequence[index_value]
        else:
            print("Index out of range. Please enter a valid index.")
    except ValueError:
        print("Invalid input. Please enter an integer.")

# Example usage:
result = get_value_at_index()
if result is not None:
    print(f"Value at the given index: {result}")