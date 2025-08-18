import ctypes

def memcpy(destination, source, num_bytes):
    # Ensure that we are not copying more than available in both buffers.
    if len(source) < num_bytes or len(destination) < num_bytes:
        raise ValueError("Source or destination buffer is too small for the number of bytes to copy.")
    
    # Copy memory using ctypes
    ctypes.memmove(ctypes.addressof(ctypes.create_string_buffer(destination)), 
                   ctypes.addressof(ctypes.create_string_buffer(source)), 
                   num_bytes)

# Create a source and destination buffer
source = bytearray(b"Hello World")
destination = bytearray(b"\x00" * 11)  # Buffer large enough to hold "Hello"

# Copy "Hello" (5 bytes) from source to destination
memcpy(destination, source[:5], 5)

print("Source:", source)
print("Destination:", destination.decode())