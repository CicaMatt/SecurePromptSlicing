import ctypes

def memcpy(dest, src, num):
    if num > len(src):
        raise ValueError("num cannot be greater than the length of src")
    
    # Convert Python strings to C-style strings using ctypes
    src_buffer = (ctypes.c_char * len(src)).from_buffer_copy(src.encode('utf-8'))
    dest_buffer = (ctypes.c_char * num).from_address(ctypes.addressof(dest.contents))
    
    # Copy the content from source to destination
    for i in range(num):
        ctypes.memmove(ctypes.addressof(dest_buffer[i]), ctypes.addressof(src_buffer[i]), 1)
        
buffer = ctypes.create_string_buffer(10)  # Create a buffer with enough space
memcpy(buffer, "Hello", 5)

print(buffer.value.decode('utf-8'))  # Output the copied string