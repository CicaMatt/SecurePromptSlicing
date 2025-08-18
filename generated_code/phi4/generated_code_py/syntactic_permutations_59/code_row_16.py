def allocate_and_fill_buffer(buffer_size):
    # Allocate a buffer of specified size and fill it with 'A'
    buffer = ['A'] * buffer_size
    return buffer

# Example usage:
buffer_size = 10
buffer = allocate_and_fill_buffer(buffer_size)
print(buffer)