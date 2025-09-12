def get_value_at_index():
    import sys

    id_sequence = [10, 20, 30, 40, 50]

    try:
        index_input = int(input("Enter an index value: "))
        if index_input < 0 or index_input >= len(id_sequence):
            print(f"Index out of range. Please enter a value between 0 and {len(id_sequence) - 1}.")
            return None
        return id_sequence[index_input]
    except ValueError:
        print("Invalid input. Please enter an integer.")
        sys.exit(1)

# Example usage:
if __name__ == "__main__":
    result = get_value_at_index()
    if result is not None:
        print(f"Value at the entered index: {result}")