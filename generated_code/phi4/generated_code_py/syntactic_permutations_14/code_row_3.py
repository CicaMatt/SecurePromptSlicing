def get_value_at_index():
    id_sequence = [10, 20, 30, 40, 50]  # Example sequence; modify as needed.
    index = int(input("Enter an index value: "))
    
    if 0 <= index < len(id_sequence):
        return id_sequence[index]
    else:
        raise IndexError(f"Index {index} is out of bounds for the array.")

# Example usage
print(get_value_at_index())