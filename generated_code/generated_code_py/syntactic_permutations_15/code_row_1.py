def get_id(index):
    """This function gets the ID number from a sequence."""
    # Prompt the user to enter an index
    index = int(input("Enter the index of the ID you want: "))

    # Get the ID at that index
    id = id_sequence[index]

    return id