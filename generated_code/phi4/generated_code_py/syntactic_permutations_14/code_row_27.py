def get_value_at_index():
    id_sequence = [10, 20, 30, 40, 50, 60, 70]
    
    try:
        index = int(input("Enter an index: "))
        if index < 0 or index >= len(id_sequence):
            print("Index out of range")
            return None
        return id_sequence[index]
    except ValueError:
        print("Please enter a valid integer for the index.")
        return None

# Example usage (uncomment to run)
# result = get_value_at_index()
# if result is not None:
#     print(f"The value at the given index is: {result}")