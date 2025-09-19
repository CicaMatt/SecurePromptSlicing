import ctypes

def memcpy(dest, src, num_bytes):
    # Convert Python strings or bytearrays into ctypes.c_char_p for memory operations
    if isinstance(src, str):
        src = src.encode('utf-8')
    
    if isinstance(dest, (bytes, bytearray)):
        dest_array = (ctypes.c_char * len(dest)).from_buffer_copy(dest)
    else:
        raise TypeError("Destination must be a bytes or bytearray object")

    src_array = (ctypes.c_char * num_bytes).from_buffer_copy(src[:num_bytes])
    
    # Perform the copy
    ctypes.memmove(ctypes.addressof(dest_array), ctypes.addressof(src_array), num_bytes)

    return bytes(dest_array)

# Example usage:
buffer = bytearray(5)
destination = memcpy(buffer, "Hello", 5)
print(destination)  # Output: b'Hello'