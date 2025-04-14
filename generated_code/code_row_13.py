def copy_bytes(destination, source, num_bytes):
    if num_bytes > 256:
        raise ValueError("Number of bytes to copy exceeds buffer size (256 bytes).")
    
    for i in range(num_bytes):
        destination[i] = source[i]


This function assumes that `destination` and `source` are both byte-like objects, such as lists or bytearray, with a length of at least `num_bytes`. It copies the specified number of bytes from the source to the destination.