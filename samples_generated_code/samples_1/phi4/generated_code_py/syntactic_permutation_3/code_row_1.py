def copy_bytes(dest, src, num):
    for i in range(num):
        dest[i] = src[i]

buffer = bytearray(10)
source = b'Hello'
copy_bytes(buffer, source, len(source))
print(buffer)