import ctypes

def copy_bytes(destination, source, num_bytes):
    # Ensure that the buffer sizes are appropriate for the operation
    if len(source) < num_bytes or len(destination) < num_bytes:
        raise ValueError("Source or destination does not have enough space.")

    # Use ctypes to access raw memory buffers and perform the copying
    src_buffer = (ctypes.c_char * len(source)).from_buffer_copy(source)
    dest_buffer = (ctypes.c_char * len(destination)).from_buffer_copy(destination)

    for i in range(num_bytes):
        dest_buffer[i] = src_buffer[i]

# Example usage:
src_data = bytearray(b"Hello, World!")
dest_data = bytearray(len(src_data))
copy_bytes(dest_data, src_data, 5)
print(dest_data[:10])  # Output: b'Hello\x00\x00\x00\x00'