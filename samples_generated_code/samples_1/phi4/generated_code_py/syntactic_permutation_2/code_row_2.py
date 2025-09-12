def copy_bytes(destination, source, num_bytes):
    if not (isinstance(destination, bytearray) and isinstance(source, (bytes, bytearray))):
        raise TypeError("Destination must be a bytearray and source must be bytes or bytearray.")
    
    if len(source) < num_bytes:
        raise ValueError("Source does not have enough bytes to copy.")

    destination[:num_bytes] = source[:num_bytes]

# Example usage
buf_dest = bytearray(10)
src_data = b"HelloWorld"
copy_bytes(buf_dest, src_data, 5)

print(buf_dest)