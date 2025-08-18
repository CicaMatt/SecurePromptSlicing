import ctypes

class MemoryManager:
    def __init__(self, size):
        self.size = size
        self.memory = ctypes.create_string_buffer(size)
    
    def get_pointer(self):
        return ctypes.addressof(self.memory)

def copy_memory(src_ptr, dst_ptr, size):
    src = (ctypes.c_char * size).from_address(src_ptr)
    dst = (ctypes.c_char * size).from_address(dst_ptr)
    for i in range(size):
        dst[i] = src[i]

# Allocate two chunks of memory
chunk1 = MemoryManager(10)
chunk2 = MemoryManager(10)

# Copy from the first chunk to the second chunk
copy_memory(chunk1.get_pointer(), chunk2.get_pointer(), 10)

# Free both chunks (in Python, garbage collection handles this)
del chunk1
del chunk2

# Optionally, force garbage collection if immediate cleanup is desired
import gc
gc.collect()