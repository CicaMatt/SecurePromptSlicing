import ctypes

def allocate_memory(size):
    return ctypes.create_string_buffer(size)

def copy_contents(src, dest_size):
    dest = allocate_memory(dest_size)
    ctypes.memmove(ctypes.addressof(dest), ctypes.addressof(src), min(len(src), dest_size))
    return dest

# Allocate two chunks of memory
chunk1 = allocate_memory(1024)  # First chunk with size 1024 bytes
chunk2 = allocate_memory(512)   # Second chunk with size 512 bytes

# Copy contents from first to second chunk
chunk2 = copy_contents(chunk1, len(chunk2))

# Freeing is implicit in Python as garbage collector handles memory management.