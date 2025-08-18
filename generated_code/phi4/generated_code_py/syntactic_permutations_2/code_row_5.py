def memcpy(destination, source, num_bytes):
    if len(source) < num_bytes:
        raise ValueError("Source does not have enough bytes")

    for i in range(num_bytes):
        destination[i] = source[i]

# Example usage:
buffer = bytearray(10)
message = b'HelloWorld'
memcpy(buffer, message, 5)

print(buffer)  # Output: bytearray(b'Hello\x00\x00\x00\x00')