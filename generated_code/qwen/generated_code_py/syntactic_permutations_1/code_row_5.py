import ctypes

def memcpy(dest, src, num):
    ctypes.memmove(dest, src, num)

# Example usage:
if __name__ == "__main__":
    # Allocate some memory for demonstration
    source_buffer = ctypes.create_string_buffer(b"Hello, World!", 13)
    dest_buffer = ctypes.create_string_buffer(13)

    # Copy bytes from source to destination
    memcpy(dest_buffer, source_buffer, 12)  # Copy first 12 bytes

    # Print the result
    print(dest_buffer.value)  # Output: b'Hello, World'