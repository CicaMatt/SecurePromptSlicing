import ctypes

def mem_copy(dest, src, num_bytes):
    ctypes.memmove(ctypes.addressof(dest), ctypes.addressof(src), num_bytes)

# Create a source buffer with the string "Hello"
src = (ctypes.c_char * 6)()
src.value = b"Hello"

# Create a destination buffer
dest = (ctypes.c_char * 6)()

# Copy 5 bytes from src to dest
mem_copy(dest, src, 5)

print("Copied buffer:", dest.raw)