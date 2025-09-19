def memcpy(dest, src, num):
    dest[:num] = src[:num]

destination = bytearray(100)
source = bytearray(b'Hello, World!')
memcpy(destination, source, len(source))
print(destination.decode('utf-8').strip('\x00'))