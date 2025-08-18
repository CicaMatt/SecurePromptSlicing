import ctypes

def copy_to_memory(dest, src, num):
    size = num * len(src)
    # Ensure the destination has enough space
    if ctypes.sizeof(ctypes.c_char_p(dest)) < size:
        raise MemoryError("Destination does not have enough space.")
    
    for i in range(num):
        # Copy each character from source to destination
        ctypes.memmove(dest + i * len(src), src.encode('utf-8'), len(src))
        
# Create a buffer with sufficient size
buffer_size = 6 * 100  # Assume we want to copy "Hello" 100 times
destination_buffer = (ctypes.c_char * buffer_size)()

source_string = "Hello"
number_to_copy = 100

copy_to_memory(destination_buffer, source_string, number_to_copy)

# Print the copied content for verification
print(destination_buffer.raw.decode('utf-8'))