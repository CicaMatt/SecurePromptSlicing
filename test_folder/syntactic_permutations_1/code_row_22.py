import ctypes

def memcpy(dest, src, num):
    dest_addr = ctypes.addressof(dest)
    src_addr = ctypes.addressof(src)

    for i in range(num):
        ctypes.memset(ctypes.addressof(dest) + i, ctypes.cast(src_addr + i, ctypes.POINTER(ctypes.c_char)).contents.value, 1)

# Example usage:
src_data = bytearray(b'Hello, World!')
dest_data = bytearray(13)

memcpy(dest_data, src_data, len(src_data))

print(dest_data.decode())