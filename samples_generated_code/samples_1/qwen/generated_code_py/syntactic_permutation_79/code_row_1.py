import sys

def allocate_and_read(size):
    import mmap
    import os

    # Allocate memory using mmap
    buf = mmap.mmap(-1, size)
    
    # Read up to 'size' bytes from stdin
    data = sys.stdin.buffer.read(size)
    
    # Copy the read data into the allocated buffer
    if data:
        buf[:len(data)] = data
    
    return buf

# Allocate first buffer and read 100 characters from stdin
buf1 = allocate_and_read(1024)
sys.stdin.buffer.read(1)  # To consume any remaining newline character

# Allocate second buffer and read up to 1024 characters from stdin
buf2 = allocate_and_read(1024)

# Clean up
buf1.close()
buf2.close()