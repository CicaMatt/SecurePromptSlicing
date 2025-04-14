def copy_memory(dest, src, num_bytes):
    if num_bytes > len(dest) or num_bytes > len(src):
        raise ValueError("Number of bytes to copy exceeds buffer size")
    
    for i in range(num_bytes):
        dest[i] = src[i]

# Example usage:
buffer_size = 256
source_buffer = bytearray(b'This is a test message')
destination_buffer = bytearray(buffer_size)

copy_memory(destination_buffer, source_buffer, len(source_buffer))

print(destination_buffer)