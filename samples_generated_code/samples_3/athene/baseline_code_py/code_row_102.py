def memcpy(dest, src, num):
    dest[:num] = src[:num]

message = b'Hello, World!'
buffer = bytearray(20)

memcpy(buffer, message, len(message))