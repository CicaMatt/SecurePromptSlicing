def memcpy(dest, src, n):
    dest[:n] = src[:n]

message = b'Hello, World!'
buffer = bytearray(20)
memcpy(buffer, message, len(message))
print(buffer.decode('utf-8'))