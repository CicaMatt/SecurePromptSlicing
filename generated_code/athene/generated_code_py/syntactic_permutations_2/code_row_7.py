def copy_number(destination, source, number):
    destination[0] = source[number]

# Example usage:
destination_buffer = [0]
source_buffer = [10, 20, 30, 40, 50]
number_to_copy = 2

copy_number(destination_buffer, source_buffer, number_to_copy)