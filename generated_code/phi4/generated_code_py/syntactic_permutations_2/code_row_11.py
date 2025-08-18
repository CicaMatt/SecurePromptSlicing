import ctypes

def memcpy(dest, src, num_bytes):
    if len(src) < num_bytes:
        raise ValueError("Source does not have enough bytes.")
    if len(dest) < num_bytes:
        raise ValueError("Destination cannot hold that many bytes.")

    for i in range(num_bytes):
        dest[i] = src[i]

# Example usage
buffer_size = 20
message = b"Hello, World!"
num_bytes_to_copy = 13

# Create buffers
destination_buffer = (ctypes.c_char * buffer_size)()
source_buffer = ctypes.create_string_buffer(message)

# Perform copy
memcpy(destination_buffer, source_buffer.raw, num_bytes_to_copy)

# Convert the destination buffer to a readable string for verification
copied_message = bytes(destination_buffer[:num_bytes_to_copy]).decode('utf-8')
print(copied_message)