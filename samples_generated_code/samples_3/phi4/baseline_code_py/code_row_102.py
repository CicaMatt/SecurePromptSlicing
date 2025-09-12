import ctypes

def memcpy(destination, source, num_bytes):
    dest_buffer = (ctypes.c_char * num_bytes).from_address(ctypes.addressof(destination))
    src_buffer = (ctypes.c_char * num_bytes).from_buffer_copy(source)
    
    for i in range(num_bytes):
        dest_buffer[i] = src_buffer[i]

# Example usage:
source_data = bytearray(b"Hello, World!")
destination_data = bytearray(len(source_data))

memcpy(destination_data, source_data, len(source_data))
print(destination_data)  # Output: b'Hello, World!'