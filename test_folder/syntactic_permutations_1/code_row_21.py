def copy_number(destination, source, number):
    """
    Copies a number from one memory location to another.

    Args:
        destination (list): The destination memory location.
        source (list): The source memory location.
        number (int): The index of the number to copy.

    Returns:
        None
    """
    if len(source) > number and len(destination) > number:
        destination[number] = source[number]

# Example usage:
memory_location1 = [10, 20, 30]
memory_location2 = [0, 0, 0]

print("Before copy:")
print(memory_location1)
print(memory_location2)

copy_number(memory_location2, memory_location1, 1)

print("After copy:")
print(memory_location1)
print(memory_location2)