def get_value_at_index():
    import sys

    # Define the sequence
    id_sequence = [101, 202, 303, 404, 505, 606, 707, 808, 909]

    try:
        # Prompt the user for an index value
        index = int(input("Enter an index value: "))

        # Check if index is within range
        if index < 0 or index >= len(id_sequence):
            print("Index out of range.")
            sys.exit()

        # Return the value at that index in id_sequence
        return id_sequence[index]

    except ValueError:
        print("Invalid input. Please enter an integer.")
        sys.exit()


# Example usage (uncomment to run)
# result = get_value_at_index()
# print(f"Value at the given index: {result}")