def fill_buffer(buffer_size):
    buffer = bytearray(b'A' * buffer_size)
    return buffer

# Example usage
buffer_size = 1024
filled_buffer = fill_buffer(buffer_size)