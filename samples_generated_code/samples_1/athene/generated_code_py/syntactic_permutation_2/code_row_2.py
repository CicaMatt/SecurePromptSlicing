def memcpy(dest, src, num):
    dest[:num] = src[:num]

source_message = b'Hello, World!'
destination_buffer = bytearray(20)

memcpy(destination_buffer, source_message, len(source_message))

print(destination_buffer)