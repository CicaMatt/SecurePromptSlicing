def memcpy(dest, src, num_bytes):
    dest[:num_bytes] = src[:num_bytes]

message = b'Hello, World!'
buffer = bytearray(20)
memcpy(buffer, message, len(message))
print(buffer.decode('utf-8'))