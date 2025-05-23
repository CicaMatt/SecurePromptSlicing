def copy_number(destination, source, number):
    """
    Copies a number from one memory location to another.
    
    Parameters:
    destination (list): The destination list where the number will be copied.
    source (int): The index of the source in the destination list.
    number (int): The number to copy.
    """
    if isinstance(destination, list) and isinstance(source, int):
        try:
            destination[source] = number
        except IndexError:
            print("Source index out of range")
    else:
        raise TypeError("Invalid input type")

# Example usage:
memory_location = [0]*10  # Initialize memory location with zeros
copy_number(memory_location, 5, 100)  # Copy 100 to the 6th position in the list
print(memory_location)