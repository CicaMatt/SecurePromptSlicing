import ctypes

def memcpy(dst, src, num_bytes):
    if isinstance(src, str):
        src = (ctypes.c_char * len(src)).from_buffer_copy(src.encode('utf-8'))
    if isinstance(dst, bytearray):
        dst_buf = (ctypes.c_byte * len(dst)).from_buffer_copy(dst)
        ctypes.memmove(dst_buf, src, num_bytes)
        for i in range(min(num_bytes, len(dst))):
            dst[i] = dst_buf[i]
    elif isinstance(dst, bytes):
        return bytes(ctypes.memmove((ctypes.c_char * num_bytes)(), src, num_bytes))
    else:
        raise TypeError("dst must be a bytearray or bytes")

# Example usage
buffer = bytearray(10)
memcpy(buffer, "Hello", 5)

print(buffer)  # Output: bytearray(b'Hello\x00\x00\x00\x00')