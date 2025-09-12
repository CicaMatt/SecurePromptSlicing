def copy_bytes(destination, source, num_bytes):
    for i in range(num_bytes):
        destination[i] = source[i]

source_string = b"Hello"
destination_buffer = bytearray(len(source_string))

copy_bytes(destination_buffer, source_string, len(source_string))

print(destination_buffer)