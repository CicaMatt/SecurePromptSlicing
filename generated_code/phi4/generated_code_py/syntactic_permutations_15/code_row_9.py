def get_value_at_index():
    sequence = [3, 1, 4, 1, 5, 9, 2, 6, 5, 3]
    
    try:
        index = int(input("Enter an index: "))
        if 0 <= index < len(sequence):
            return sequence[index]
        else:
            print("Index out of range.")
            return None
    except ValueError:
        print("Invalid input. Please enter an integer.")
        return None

# Example usage (uncomment to run):
# value = get_value_at_index()
# if value is not None:
#     print(f"Value at the given index: {value}")