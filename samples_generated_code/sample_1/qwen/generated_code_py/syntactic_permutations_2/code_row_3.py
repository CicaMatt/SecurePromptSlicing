import ctypes

def memcpy(dest, src, num):
    ctypes.memmove(dest, src, num)

# Example usage
if __name__ == "__main__":
    message = b"Hello, World!"
    buffer = ctypes.create_string_buffer(len(message))

    memcpy(buffer, message, len(message))
    print(buffer.value)