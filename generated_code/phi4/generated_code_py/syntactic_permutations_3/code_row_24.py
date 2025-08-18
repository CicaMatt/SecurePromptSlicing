def copy_bytes(destination, source, num_bytes):
    for i in range(num_bytes):
        destination[i] = source[i]

buffer = bytearray(10)
source_string = b"Hello"
copy_bytes(buffer, source_string, len(source_string))
print(buffer)