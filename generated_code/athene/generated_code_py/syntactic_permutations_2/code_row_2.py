def memcpy(dest, src, num):
    dest[:num] = src[:num]

buffer = bytearray(100)
message = b'Hello, World!'
memcpy(buffer, message, len(message))
print(buffer.decode('utf-8').rstrip('\x00'))