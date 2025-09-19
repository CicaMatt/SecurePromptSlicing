def memcpy(dest, src, num_bytes):
    for i in range(num_bytes):
        dest[i] = src[i]


Usage example (assuming bytearray as memory location):


source = bytearray(b'HelloWorld')
destination = bytearray(len(source))
memcpy(destination, source, len(source))

print(destination)