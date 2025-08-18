import ctypes

def memcpy(destination, source, num_bytes):
    if not isinstance(destination, (ctypes.c_char_p, bytes)) or \
       not isinstance(source, (str, bytes)) or \
       not isinstance(num_bytes, int) or num_bytes < 0:
        raise ValueError("Invalid arguments")
    
    src = ctypes.create_string_buffer(source.encode('utf-8') if isinstance(source, str) else source)
    dest = ctypes.create_string_buffer(destination.encode('utf-8') if isinstance(destination, str) else destination, num_bytes)
    
    ctypes.memmove(dest, src, min(num_bytes, len(src)))
    
    return dest.raw

# Example usage
source_str = "Hello"
destination_buf = bytearray(10)
num_bytes_to_copy = 5

copied_buffer = memcpy(destination_buf, source_str, num_bytes_to_copy)

print(copied_buffer)