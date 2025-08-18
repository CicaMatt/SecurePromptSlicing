import ctypes

def memcpy(destination, source, num_bytes):
    ctypes.memmove(destination, source, num_bytes)

# Example usage
if __name__ == "__main__":
    message = b"Hello, World!"
    buffer = ctypes.create_string_buffer(len(message))
    
    memcpy(buffer, message, len(message))
    
    print(buffer.value)