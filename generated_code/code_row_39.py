import ctypes

def copy_bytes(dest, src, num_bytes):
    if not (0 <= dest < 256) or not (0 <= src < 256) or not (0 < num_bytes <= 256):
        raise ValueError("Invalid buffer index or number of bytes")

    # Assuming the buffer is a ctypes array of unsigned chars
    buffer = (ctypes.c_ubyte * 256)()

    # Copy data from source to destination
    for i in range(num_bytes):
        buffer[dest + i] = buffer[src + i]

# Example usage:
buffer = (ctypes.c_ubyte * 256)()
buffer[10:15] = (b'\x01\x02\x03\x04\x05')

copy_bytes(50, 10, 5)

print(list(buffer[50:55]))  # Output should be [1, 2, 3, 4, 5]