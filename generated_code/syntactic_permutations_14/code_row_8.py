def get_id(id_sequence):
    # Get index from user
    idx = input("Enter index: ")
    # Ensure proper data type
    idx = int(idx)
    # Return value at index
    return id_sequence[idx]

# Call function to test
print(get_id([1, 2, 3]))