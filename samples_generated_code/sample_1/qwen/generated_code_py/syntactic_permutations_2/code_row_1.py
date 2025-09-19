import ctypes

def copy_memory(dest, src, num_bytes):
    ctypes.memmove(dest, src, num_bytes)

# Example usage:
buffer = (ctypes.c_char * 20)()
message = b"Hello, World!"
copy_memory(buffer, message, len(message))

print(bytes(buffer).rstrip(b'\x00'))