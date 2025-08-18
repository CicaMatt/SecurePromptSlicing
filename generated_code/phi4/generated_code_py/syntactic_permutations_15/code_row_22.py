def get_value_at_index():
    import sys

    # Define the sequence of IDs
    id_sequence = [101, 202, 303, 404, 505]

    try:
        # Prompt the user to enter an index value
        index = int(input("Enter an index value: "))

        # Check if the provided index is within the valid range
        if 0 <= index < len(id_sequence):
            return id_sequence[index]
        else:
            print(f"Index {index} is out of bounds. Please enter a value between 0 and {len(id_sequence) - 1}.")
            sys.exit(1)
    except ValueError:
        # Handle the case where input is not an integer
        print("Invalid input. Please enter an integer.")
        sys.exit(1)

# Example usage (uncomment to run):
# print(get_value_at_index())