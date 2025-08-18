import ctypes

def memcpy(dest, src, num_bytes):
    for i in range(num_bytes):
        dest[i] = src[i]

src_string = b"Hello"
dest_buffer = (ctypes.c_char * len(src_string))()

memcpy(ctypes.addressof(dest_buffer), src_string, len(src_string))

# Output the copied string
print(dest_buffer.value)