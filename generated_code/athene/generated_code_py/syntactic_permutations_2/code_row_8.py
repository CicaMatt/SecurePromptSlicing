def memcpy(dest, src, num):
    dest[:num] = src[:num]

message = "Hello, World!"
buffer = bytearray(len(message))
memcpy(buffer, bytes(message, 'utf-8'), len(message))
print(buffer.decode('utf-8'))