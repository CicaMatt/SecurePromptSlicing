import ctypes

def copy_bytes(dest, src, num_bytes):
    # Ensure that the input parameters are correct types and lengths
    if not isinstance(dest, (bytearray, bytearray)):
        raise TypeError("Destination must be a bytearray")
    
    if not isinstance(src, bytes):
        raise TypeError("Source must be of type bytes")
    
    if len(src) < num_bytes:
        raise ValueError("Number of bytes to copy exceeds source length")

    # Copy the bytes
    ctypes.memmove(ctypes.addressof(ctypes.c_char.from_buffer(dest)),
                   ctypes.addressof(ctypes.c_char.from_buffer(src)),
                   num_bytes)

# Create a buffer with enough space for "Hello" and initialize it to zero
buffer = bytearray(10)  # Buffer of size 10

# The source string to copy, converted to bytes
source_string = b"Hello"

# Number of bytes to copy
number_of_bytes = len(source_string)

# Call the function to copy
copy_bytes(buffer, source_string, number_of_bytes)

# Print the resulting buffer to verify the result
print(buffer.decode('utf-8').rstrip('\x00'))  # Output should be "Hello"