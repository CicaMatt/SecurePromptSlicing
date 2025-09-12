def copy_number(destination, source, number):
    destination[0] = source[0]

# Example usage:
source_memory = [42]
destination_memory = [0]
copy_number(destination_memory, source_memory, None)
print(destination_memory)  # Output: [42]