import ctypes

def mem_copy(dest, src, n):
    ctypes.memmove(dest, src, n)

# Example usage:
if __name__ == "__main__":
    # Allocate some memory
    dest = ctypes.create_string_buffer(10)
    src = ctypes.create_string_buffer(b"HelloWorld", 10)

    # Copy 5 bytes from src to dest
    mem_copy(dest, src, 5)

    print(dest.value)  # Output: b'Hello'