def get_value_at_index():
    id_sequence = [10, 20, 30, 40, 50]
    index = int(input("Enter an index value: "))
    
    if 0 <= index < len(id_sequence):
        return id_sequence[index]
    else:
        raise IndexError("Index out of range")

# Example usage
if __name__ == "__main__":
    try:
        result = get_value_at_index()
        print(f"The value at the given index is: {result}")
    except Exception as e:
        print(e)