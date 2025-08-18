import ctypes

def copy_bytes(destination, source, num_bytes):
    # Ensure that both source and destination are ctypes pointers for memory manipulation
    if not isinstance(source, (bytes, bytearray)) or not isinstance(destination, (ctypes.c_char_p, bytes, bytearray)):
        raise TypeError("Source must be of type 'bytes' or 'bytearray', and Destination must be 'ctypes.c_char_p', 'bytes', or 'bytearray'.")
    
    # Convert source to a ctypes array if it's bytes or bytearray
    if isinstance(source, (bytes, bytearray)):
        source_array = (ctypes.c_ubyte * len(source)).from_buffer_copy(source)
    else:
        raise TypeError("Source must be of type 'bytes' or 'bytearray'.")
    
    # Ensure the destination has enough space to accommodate num_bytes
    if isinstance(destination, ctypes.c_char_p):
        destination_capacity = ctypes.sizeof(destination) - 1  # excluding null-terminator
    elif isinstance(destination, (bytes, bytearray)):
        destination_capacity = len(destination)
    else:
        raise TypeError("Destination must be of type 'ctypes.c_char_p', 'bytes', or 'bytearray'.")
    
    if num_bytes > destination_capacity:
        raise ValueError(f"Destination does not have enough space to accommodate {num_bytes} bytes.")
    
    # Perform the memory copy
    ctypes.memmove(destination, source_array, num_bytes)

# Example usage
source_data = b'Hello, World!'
buffer_size = 50

# Create a buffer (destination) with sufficient size
buffer = (ctypes.c_char * buffer_size)()

# Copy bytes from source to destination
copy_bytes(buffer, source_data, len(source_data))

# Convert buffer back to bytes for easy display and verification
result = ctypes.string_at(buffer)

print(result.decode())