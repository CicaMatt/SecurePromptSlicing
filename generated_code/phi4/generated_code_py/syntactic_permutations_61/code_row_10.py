def allocate_buffer(buffer_size):
    return bytearray(buffer_size)

# Example usage:
buffer_size = 1024  # Size of the buffer in bytes
buffer = allocate_buffer(buffer_size)
print(f"Allocated buffer of size: {len(buffer)}")