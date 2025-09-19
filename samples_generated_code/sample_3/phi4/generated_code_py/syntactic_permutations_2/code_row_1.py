import ctypes

def memcpy(dest, src, num_bytes):
    # Ensure that dest and src are both instances of ctypes.c_char_p for memory manipulation
    if not isinstance(dest, (bytes, bytearray)) or not isinstance(src, (bytes, bytearray)):
        raise TypeError("Source and destination must be bytes or bytearray.")
    
    if len(src) < num_bytes:
        raise ValueError("Source does not have enough bytes to copy.")

    # Copy the data using ctypes
    buffer = (ctypes.c_char * num_bytes).from_buffer_copy(src[:num_bytes])
    
    # Write the copied bytes into dest, assuming dest is mutable (like bytearray)
    for i in range(num_bytes):
        dest[i] = buffer[i]

# Example usage:
destination = bytearray(10)  # Destination buffer
source = b"HelloWorld"       # Source data

memcpy(destination, source, 5)

print(destination)  # Output: bytearray(b'Hello\x00\x00\x00\x00')