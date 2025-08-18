def get_value_from_index():
    id_sequence = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    index = int(input("Enter an index value: "))
    
    if 0 <= index < len(id_sequence):
        return id_sequence[index]
    else:
        print("Index out of range.")
        return None

# Example usage
if __name__ == "__main__":
    result = get_value_from_index()
    if result is not None:
        print(f"Value at the given index: {result}")