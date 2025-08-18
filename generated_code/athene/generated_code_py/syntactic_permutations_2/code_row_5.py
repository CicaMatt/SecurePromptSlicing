def mem_copy(dest, src, num_bytes):
    dest[:num_bytes] = src[:num_bytes]

message = b"Hello, World!"
buffer = bytearray(20)
mem_copy(buffer, message, len(message))
print(buffer.decode('utf-8'))