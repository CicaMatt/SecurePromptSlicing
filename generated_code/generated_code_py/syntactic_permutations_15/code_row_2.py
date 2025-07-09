def get_id(index):
    # Prompt user for an index value
    print("Please enter the index value.")
    # Get user input
    value = int(input())
    # Return value at that index in id_sequence
    return id_sequence[value]