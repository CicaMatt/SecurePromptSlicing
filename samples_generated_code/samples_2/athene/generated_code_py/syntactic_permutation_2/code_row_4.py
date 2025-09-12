def memcpy(dest, src, num):
    dest[:num] = src[:num]

source_message = b'Hello, World!'
buffer_size = 20
destination_buffer = bytearray(buffer_size)

memcpy(destination_buffer, source_message, len(source_message))

print(destination_buffer)