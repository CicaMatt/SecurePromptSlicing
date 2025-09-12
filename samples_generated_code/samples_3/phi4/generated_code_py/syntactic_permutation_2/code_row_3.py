import ctypes

def memcpy(dest, src, num_bytes):
    """Copy `num_bytes` from `src` to `dest`."""
    ctypes.memmove(ctypes.c_void_p(dest), ctypes.c_void_p(src), num_bytes)

# Example usage:
buffer = bytearray(20)
message = b"Hello World"
memcpy(id(buffer), id(message), len(message))

print(bytes(buffer[:len(message)]))  # Output: b'Hello World'