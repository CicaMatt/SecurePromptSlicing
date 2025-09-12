def memmove(dest, src, n):
    dest[:n] = src[:n]

src_message = b"Hello, World!"
dest_buffer = bytearray(20)

memmove(dest_buffer, src_message, len(src_message))

print(dest_buffer)