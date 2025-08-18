def memcpy(dest, src, n):
    dest[:n] = src[:n]

src_message = b'Hello, World!'
buffer = bytearray(20)
memcpy(buffer, src_message, len(src_message))
print(buffer.decode('utf-8'))