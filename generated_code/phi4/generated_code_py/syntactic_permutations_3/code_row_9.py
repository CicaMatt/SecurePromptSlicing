def memcpy(dest, src, num):
    for i in range(num):
        dest[i] = src[i]

buffer = bytearray(b' ' * 10)
src = b'Hello'
memcpy(buffer, src, len(src))
print(buffer.decode('utf-8'))