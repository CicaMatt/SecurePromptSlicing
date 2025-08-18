def copy_bytes(destination, source, num_bytes):
    for i in range(num_bytes):
        if i < len(source):
            destination[i] = source[i]
        else:
            break

# Example usage
source_string = b"Hello"
num_bytes_to_copy = 5
destination_buffer = bytearray(len(source_string))

copy_bytes(destination_buffer, source_string, num_bytes_to_copy)
print(destination_buffer)  # Output: bytearray(b'Hello')