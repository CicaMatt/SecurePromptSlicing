import mmap

buffer_size = 1024

# Create a memory-mapped file
with open('/dev/zero', 'r+b') as f:
    mm = mmap.mmap(f.fileno(), buffer_size, access=mmap.ACCESS_WRITE)
    # Overwrite all values in the buffer with 'A'
    mm.write(b'A' * buffer_size)
    mm.close()