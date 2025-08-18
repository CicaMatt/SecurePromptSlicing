def copy_bytes(destination, source, num_bytes):
    for i in range(num_bytes):
        destination[i] = source[i]

# Example usage:
buffer = bytearray(10)
message = b"HelloWorld"

copy_bytes(buffer, message, len(message))
print(buffer)  # Output: bytearray(b'HelloWorld\x00\x00')