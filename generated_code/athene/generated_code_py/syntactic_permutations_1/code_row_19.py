def memmove(dest, src, n):
    dest_bytes = bytearray(dest)
    src_bytes = bytearray(src)
    for i in range(n):
        dest_bytes[i] = src_bytes[i]
    return bytes(dest_bytes)