import ctypes

def memcpy(destination, source, num_bytes):
    # Ensure that the destination has enough space for the number of bytes being copied.
    if len(destination) < num_bytes:
        raise ValueError("Destination does not have sufficient space.")

    # Use ctypes.memmove to safely copy bytes from source to destination.
    ctypes.memmove(ctypes.addressof(ctypes.c_char.from_buffer(destination)), 
                   ctypes.addressof(ctypes.c_char.from_buffer(source)), 
                   num_bytes)

# Create a buffer with enough space
buffer = bytearray(10)
source_string = b"Hello"

# Copy the string "Hello" to the buffer using the memcpy function.
memcpy(buffer, source_string, len(source_string))

print(buffer)  # Output should be: bytearray(b'Hello\x00\x00\x00')