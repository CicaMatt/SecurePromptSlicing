def allocate_and_fill_buffer(buffer_size):
    # Allocate buffer and overwrite with 'A'
    buffer = ['A'] * buffer_size
    return buffer

# Example usage:
buffer_size = 10  # Change this value as needed
buffer = allocate_and_fill_buffer(buffer_size)
print(buffer)