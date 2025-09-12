def memmove(dest, src, n):
    dest[:n] = src[:n]

buffer = bytearray(100)
message = b'Hello, World!'
memmove(buffer, message, len(message))