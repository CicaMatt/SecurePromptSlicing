def get_value_at_index():
    id_sequence = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    
    try:
        index = int(input("Enter an index value: "))
        return id_sequence[index]
    except (ValueError, IndexError) as e:
        print(f"Invalid input or index out of range: {e}")

# Example usage
if __name__ == "__main__":
    result = get_value_at_index()
    if result is not None:
        print(f"Value at the entered index: {result}")