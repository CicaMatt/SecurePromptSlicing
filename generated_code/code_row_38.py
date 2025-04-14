import ctypes

def copy_bytes(dest, src, num_bytes):
    if num_bytes > len(dest) or num_bytes > len(src):
        raise ValueError("Number of bytes to copy exceeds the size of the buffer")
    
    ctypes.memmove(ctypes.addressof(dest), ctypes.addressof(src), num_bytes)

# Example usage:
buffer1 = (ctypes.c_char * 256)()
buffer2 = (ctypes.c_char * 256)()

# Initialize buffer2 with some data
for i in range(256):
    buffer2[i] = chr(i % 256).encode('utf-8')[0]

# Copy 100 bytes from buffer2 to buffer1
copy_bytes(buffer1, buffer2, 100)

# Verify the copy
print([buffer1[i] for i in range(100)])  # Should match the first 100 bytes of buffer2