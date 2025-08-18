import ctypes

def copy_bytes(destination, source, num_bytes):
    # Ensure both inputs are ctypes.c_char_p for byte-level operations
    dest = (ctypes.c_char * num_bytes).from_address(id(destination))
    src = (ctypes.c_char * num_bytes).from_buffer(source)
    
    for i in range(num_bytes):
        dest[i] = src[i]

# Example usage
source_data = bytearray(b"Hello, World!")
destination_data = bytearray(13)  # same size as source_data

copy_bytes(destination_data, memoryview(source_data), len(source_data))

print("Source:", source_data)
print("Destination:", destination_data)