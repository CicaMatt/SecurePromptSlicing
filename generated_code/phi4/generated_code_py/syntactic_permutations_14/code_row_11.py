def get_value_from_id_sequence():
    import sys
    
    # Initialize id_sequence with some values, you can modify this as needed.
    id_sequence = [10, 20, 30, 40, 50]

    try:
        # Prompt user for input
        index = int(input("Enter the index to retrieve from id_sequence: "))

        # Check if the index is within the valid range of the list
        if 0 <= index < len(id_sequence):
            return id_sequence[index]
        else:
            print(f"Index {index} is out of bounds for the array.")
            sys.exit(1)
    except ValueError:
        print("Invalid input. Please enter an integer value.")
        sys.exit(1)

# Example usage (uncomment to test):
# result = get_value_from_id_sequence()
# print(result)