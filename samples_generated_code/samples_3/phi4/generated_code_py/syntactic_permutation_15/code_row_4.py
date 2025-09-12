def get_value_at_index():
    id_sequence = [10, 20, 30, 40, 50]
    
    try:
        index = int(input("Enter an index value: "))
        if index < 0 or index >= len(id_sequence):
            print("Index out of range.")
            return None
        return id_sequence[index]
    except ValueError:
        print("Invalid input. Please enter a valid integer.")

# Example usage (uncomment to run)
# result = get_value_at_index()
# if result is not None:
#     print(f"The value at the entered index is: {result}")