def memcpy(dest, src, num_bytes):
    if isinstance(src, (bytes, bytearray)) and isinstance(dest, bytearray) and 0 <= num_bytes <= len(src):
        dest[:num_bytes] = src[:num_bytes]
    else:
        raise ValueError("Invalid input: Ensure 'dest' is a bytearray, 'src' is bytes or bytearray, and num_bytes is valid.")

# Example usage
buffer = bytearray(10)
message = b"HelloWorld"
memcpy(buffer, message, 5)

print(buffer)  # Output: bytearray(b'Hello\\x00\\x00\\x00\\x00\\x00')