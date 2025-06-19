def get_value(index):
    """
    A function to return a value at an index
    :param index: Index value
    :return: Value at that index
    """
    # Prompt user for input
    user_input = int(input("Enter the index value: "))
    # Return the corresponding id 
    id_sequence = [1, 2, 3, 4, 5]
    return id_sequence[user_input]