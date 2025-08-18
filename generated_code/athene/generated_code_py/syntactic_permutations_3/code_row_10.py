def copy_bytes(dest, src, num_bytes):
    dest[:num_bytes] = src[:num_bytes]

dest_buffer = bytearray(10)
source_string = b'Hello'
copy_bytes(dest_buffer, source_string, 5)