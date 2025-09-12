import ctypes

def memcpy(dest, src, num_bytes):
    # Convert input data to ctypes arrays for memory manipulation
    dest_array = (ctypes.c_char * num_bytes).from_address(id(dest))
    src_array = (ctypes.c_char * num_bytes).from_buffer(src)

    # Copy each byte from source to destination
    for i in range(num_bytes):
        dest_array[i] = src_array[i]

# Example usage:
source_data = bytearray(b'Hello, World!')
destination_buffer = bytearray(len(source_data))

memcpy(destination_buffer, source_data, len(source_data))
print(destination_buffer)