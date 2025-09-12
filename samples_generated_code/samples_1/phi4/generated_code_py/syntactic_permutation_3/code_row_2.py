import ctypes

def mem_copy(dest, src, num_bytes):
    # Create a mutable byte array from the source string with the given size.
    src_array = bytearray(src.encode('utf-8')[:num_bytes])

    # Copy bytes into destination using ctypes
    dest_array = (ctypes.c_char * num_bytes).from_buffer(dest)
    for i in range(num_bytes):
        dest_array[i] = src_array[i]

# Example usage:
buffer_size = 6
source_string = "Hello"
destination_buffer = bytearray(buffer_size)

mem_copy(destination_buffer, source_string, buffer_size)

print("Buffer after copy:", destination_buffer.decode('utf-8', errors='ignore'))